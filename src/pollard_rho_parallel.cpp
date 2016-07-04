/*
 * Implementation of Pollard's rho algorithm (Single Processor)
 *
 * Author: Rodrigo
 * Date: 31/10/2015
 * License: LGPL. No copyright.
 */
#include <iostream>
#include <map>
#include <vector>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "bigint.h"
#include "elliptic_curve.h"
#include "point.h"
#include "pollard_rho.h"

using namespace std;

bool isDistinguished(const Point&);
BigInt popcount(const BigInt&);

BigInt L(64);
vector<BigInt> c, d;
vector<Point> R;
vector<int> pids;
int fd[2]; // Pipe

void sendToServer(const BigInt &num)
{
    const char *str = num.c_str();
    int len = strlen(str) + 1;
    write(fd[1], &len, sizeof(int));
    write(fd[1], str, len);
}

void worker_func(Params params)
{
    auto E = *params.E;
    auto P = *params.P;
    auto Q = *params.Q;

    BigInt k = E.order();
    BigInt a = BigInt::random(k);
    BigInt b = BigInt::random(k);
    Point X = P*a + Q*a;

    while (1)
    {
        if (isDistinguished(X)) {
            sendToServer(a);
            sendToServer(b);
            sendToServer(E.A());
            sendToServer(E.B());
            sendToServer(E.field());
            sendToServer(E.order());
            sendToServer(X.x());
            sendToServer(X.y());
        }

        int i = H(X, L).get_ui();
        X += R[i];
        a += c[i];
        b += d[i];
    }
}

BigInt recvFromWorker()
{
    int size = 0;
    read(fd[0], &size, sizeof(int));
    if (size > 100) size = 100;
    char *str = (char*) calloc(size, 1);
    read(fd[0], str, size);
    return BigInt(str);
}

BigInt server_func(const BigInt &k)
{
    map<string, vector<BigInt>> triples;
    Args triple_collided;

    // cout << "Server PID: " << getpid() << endl;
    while (1)
    {
        // string _a, _b, _x, _y;
        string _A, _B, _field, _order;

        BigInt a = recvFromWorker();
        BigInt b = recvFromWorker();
        BigInt A = recvFromWorker();
        BigInt B = recvFromWorker();
        BigInt field = recvFromWorker();
        BigInt order = recvFromWorker();
        BigInt x = recvFromWorker();
        BigInt y = recvFromWorker();

        EllipticCurve E(A, B, field, order);
        Point P = E.point(x, y);

        auto it = triples.find(P.str());
        if (it != triples.end())
        {
            // auto v = it->second;
            triple_collided = Args(a, b, P);
            break;
        }

        vector<BigInt> v;
        v.push_back(a);
        v.push_back(b);
        triples[P.str()] = v;
        triples.size();
    }

    BigInt am = triple_collided.a;
    BigInt bm = triple_collided.b;
    string P = triple_collided.P.str();
    BigInt an = triples[P][0];
    BigInt bn = triples[P][1];

    if (bn == bm)
    {
        throw domain_error("Indefined value");
    }

    BigInt f = an-am;
    BigInt g = (bm-bn).invMod(k);
    BigInt ret = (f * g) % k;
    BigInt x = (ret + k) % k;
    return x;
}

void kill_processes()
{
    for (unsigned int i = 0; i < pids.size(); i++)
    {
        kill(pids[i], SIGKILL);
    }
}

void spawn(int workers, Params params)
{
    for (int i = 0; i < workers; i++)
    {
        if (fork() == 0)
        {
            pids.push_back(getpid());
            worker_func(params);
            exit(0);
        }
    }
}

BigInt
PollardRho::parallel(EllipticCurve &E, Point &P, Point &Q) throw()
{
    BigInt an, bn;
    BigInt am, bm;

    BigInt k = E.order();

    for (int i = 0; i < L; ++i)
    {
        c.push_back(BigInt::random(k));
        d.push_back(BigInt::random(k));
        R.push_back(P*c.back() + Q*d.back());
    }

    if (pipe(fd) < 0)
    {
        cout << "Pipe failed\n";
        exit(-1);
    }

    // Creating processes
    int cores = sysconf(_SC_NPROCESSORS_ONLN);
    if (fork() == 0)
    {
        cores = 1;
        spawn(cores, Params(E, P, Q));
        exit(0);
    }

    BigInt x = server_func(k);
    // join?
    kill_processes();

    return x;
}

bool isDistinguished(const Point &P)
{
    BigInt x = P.x();
    return x.popcount() < 20;
}
