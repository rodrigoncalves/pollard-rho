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
#include <unistd.h>
#include <signal.h>
#include "bigint.h"
#include "elliptic_curve.h"
#include "point.h"
#include "pollard_rho.h"

using namespace std;

bool isDistinguished(const Point&);
BigInt popcount(const BigInt&);
void sendToServer(Args*);

BigInt L(64);
vector<BigInt> c, d;
vector<Point> R;
vector<int> pids;
int fd[2]; // Pipe

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
            Args *args = new Args(a, b, X);
            sendToServer(args);
        }

        int i = H(X, L).get_ui();
        X += R[i];
        a += c[i];
        b += d[i];
    }
}

BigInt server_func(const BigInt &k)
{
    map<string, vector<BigInt>> triples;
    Args* triple_collided = nullptr;

    while (1)
    {
        Args *args = new Args();
        read(fd[1], args, sizeof(args));
        auto a = args->a;
        auto b = args->b;
        auto P = args->P;

        auto it = triples.find(P->str());
        if (it != triples.end())
        {
            auto v = it->second;
            triple_collided = args;
            break;
        }

        triples[P->str()] = vector<BigInt>(a, b);
        delete args;
    }

    BigInt am = *triple_collided->a;
    BigInt bm = *triple_collided->b;
    string P = triple_collided->P->str();
    BigInt an = triples[P][0];
    BigInt bn = triples[P][1];
    delete triple_collided;

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

void sendToServer(Args *args)
{
    write(fd[0], (void*)args, sizeof(args));
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
    if (pipe(fd))
    {
        cout << "Pipe failed\n";
        exit(-1);
    }

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

    // Creating processes
    int cores = sysconf(_SC_NPROCESSORS_ONLN);
    spawn(cores, Params(E, P, Q));
    BigInt x = server_func(k);
    // join?
    kill_processes();

    return x;
}

bool isDistinguished(const Point &P)
{
    BigInt x = P.x();
    return x.popcount() < 24;
}
