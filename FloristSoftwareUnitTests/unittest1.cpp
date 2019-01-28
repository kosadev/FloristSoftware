#include "stdafx.h"
#include "CppUnitTest.h"
#include "../FloristSoftware/pch.h"
#include "../FloristSoftware/DbConnector.h"
#include "../FloristSoftware/FloristInterface.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FloristSoftwareUnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestConnecting)
		{
			DbConnector database((dbStr)"serwer1803050.home.pl", (dbStr)"27637716_fs", (dbStr)"HaloPolicja997", (dbStr)"27637716_fs");
			DbConnector::QueryState connectionState = database.connect();

			Assert::AreEqual((int)connectionState, (int)DbConnector::QueryState::Successed);
		}

		TEST_METHOD(TestConnectingWithWrongPassword)
		{
			DbConnector database((dbStr)"serwer1803050.home.pl", (dbStr)"27637716_fs", (dbStr)"HaloPolicja999", (dbStr)"27637716_fs");
			DbConnector::QueryState connectionState = database.connect();

			Assert::AreNotEqual((int)connectionState, (int)DbConnector::QueryState::Successed);
		}

		TEST_METHOD(TestUserConstructor) {
			User user(15, "email@email.com", "haselko", 0, 1);

			Assert::AreEqual((std::string)"email@email.com", user.getLogin());
		}

		TEST_METHOD(TestAddingUser) {
			FloristInterface *floristInterface = nullptr;

			DbConnector database((dbStr)"serwer1803050.home.pl", (dbStr)"27637716_fs", (dbStr)"HaloPolicja997", (dbStr)"27637716_fs");
			DbConnector::QueryState connectionState = database.connect();
			floristInterface = new FloristInterface(database);

			if (connectionState == DbConnector::QueryState::Successed) {
				Assert::AreEqual(true, floristInterface->addUser("test@test.com", "siemka"));
			}
		}


		TEST_METHOD(TestAddingUserWrongEmail) {
			FloristInterface *floristInterface = nullptr;

			DbConnector database((dbStr)"serwer1803050.home.pl", (dbStr)"27637716_fs", (dbStr)"HaloPolicja999", (dbStr)"27637716_fs");
			DbConnector::QueryState connectionState = database.connect();
			floristInterface = new FloristInterface(database);

			if (connectionState != DbConnector::QueryState::Successed) {
				Assert::AreNotEqual(true, floristInterface->addUser("test?test.com", "siemka"));
			}
		}
	};
}