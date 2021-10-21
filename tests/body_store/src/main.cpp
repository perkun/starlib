#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "Bodies.h"
#include "BodyStoreConverter.h"
#include "StateVector.h"

using namespace std;
using namespace StarLib;

int main(int argc, char *argv[])
{
    BodyStore store;

    vector<Body> bodies;
    int num_bodies = 10;
    bodies.reserve(num_bodies);
    for (int i = 0; i < num_bodies; i++)
    {
        char name[100];
        sprintf(name, "body nr %d, group 1", i);
        bodies.emplace_back(
            Body{name, i * 0.01,
                 StateVector(Vec3(i, i, i), Vec3(i, i, i), i * 100.0)});
    }

    GroupRef g1ref = store.add_group("test group 1", bodies);
    cout << "store size: " << store.size() << endl
         << "group name: " << g1ref.name << endl
         << "group first id: " << g1ref.first_id << endl
         << "group len: " << g1ref.length << endl;

    bodies.clear();
    bodies.reserve(num_bodies);

    for (int i = 0; i < num_bodies; i++)
    {
        char name[100];
        sprintf(name, "body nr %d, group 2", i);
        bodies.emplace_back(
            Body{name, i * 0.1,
                 StateVector(Vec3(i, i, i), Vec3(i, i, i), i * 1000.0)});
    }
    GroupRef g2ref = store.add_group("test group 2", bodies);
    cout << "store size: " << store.size() << endl
         << "group name: " << g2ref.name << endl
         << "group first id: " << g2ref.first_id << endl
         << "group len: " << g2ref.length << endl;


    // 	BodyStore store2;
    // 	BodyStoreConverter::copy_metadata(store, store2);

    vector<Body> g2 = store.get_group(g2ref);
    vector<Body> g1 = store.get_group(g1ref);

    cout << "G1: " << endl;
    for (Body &b : g1)
        cout << b.name << endl;

    cout << "G2: " << endl;
    for (Body &b : g2)
        cout << b.name << endl;


    bodies.clear();
    bodies.reserve(num_bodies*2);
	for (int i = 0; i < num_bodies * 2; i++)
	{
        char name[100];
        sprintf(name, "test body %d", i);
        bodies.emplace_back(
            Body{name, i * 0.1,
                 StateVector(Vec3(i, i, i), Vec3(i, i, i), i * 1000.0)});
	}

	BodyStore store2;
	auto gref = store2.add_group("test group", bodies);

	vector<Body> tg = store2.get_group(gref);
    cout << "\ntest group: " << endl;
    for (Body &b : tg)
        cout << b.name << endl;

	BodyStoreConverter::copy_metadata(store, store2);
    store.get_group(g2ref);
    store.get_group(g1ref);

    cout << "copy G1: " << endl;
    for (Body &b : g1)
        cout << b.name << endl;

    cout << "copy G2: " << endl;
    for (Body &b : g2)
        cout << b.name << endl;


    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
