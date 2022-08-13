#include <utility>
#include <string>
#include <vector>
#include <memory>
#include <iosfwd>  // iostream forward - speed compile, .cpp only
#include "../src/tomlcpp.h"

#include "gtest/gtest.h"

class tomlcppTest: public ::testing::Test {
public:
	tomlcppTest() {
		// You can do set-up work for each test here.
	}

	~tomlcppTest() override {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	void SetUp() override {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	void TearDown() override {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}
};

using std::cerr;
using std::cout;

TEST_F( tomlcppTest,fatal) {
//	cerr << "FATAL: " << msg << "\n";
//	fatal("msg");
}
//----------------------------------------------------------------------------------
TEST_F( tomlcppTest,TestPropRead) {
//	// 1. parse file
//	auto res = toml::parseFile("sample.toml");
//	if (!res.table) {
//		fatal("cannot parse file: " + res.errmsg);
//	}
//
//	// 2. get top level table
//	auto server = res.table->getTable("server");
//	if (!server) {
//		fatal("missing [server]");
//	}
//
//	// 3. extract values from the top level table
//	bool ok;
//	std::string host;
//	std::tie(ok, host) = server->getString("host");
//	if (!ok) {
//		fatal("missing or bad host entry");
//	}
//
//	auto portArray = server->getArray("port");
//	if (!portArray) {
//		fatal("missing 'port' array");
//	}
//
//	// 4. examine the values
//	cout << "\nhost: " << host;
//	cout << " port: ";
//	for (int i = 0;; i++) {
//		auto p = portArray->getInt(i);
//		if (!p.first)
//			break;
//
//		cout << p.second << " ";
//	}
//	cout << "\n";
}
