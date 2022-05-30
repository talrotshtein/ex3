
#include <sstream>

#include "HealthPoints.h"

namespace HealthPointsTests {

static bool checkHealthPointsValues(const HealthPoints& healthPoints, int current, int max)
{
	std::ostringstream expected;
	expected << current << '(' << max << ')';
	std::ostringstream result;
	result << healthPoints;
	return (expected.str() == result.str());
}

bool testInitialization()
{
	bool testResult = true;

	HealthPoints healthPoints1; /* has 100 points out of 100 */
	HealthPoints healthPoints2(150); /* has 150 points out of 150 */
	bool exceptionThrown = false;
	try {
		HealthPoints healthPoints3(-100);
	}
	catch (HealthPoints::InvalidArgument& e) {
		exceptionThrown = true;
	}

	testResult = testResult && exceptionThrown;
	testResult = testResult && checkHealthPointsValues(healthPoints1, 100, 100);
	return testResult;
}

bool testArithmaticOperators()
{
	bool testResult = true;
	HealthPoints healthPoints1; /* has 100 points out of 100 */
	HealthPoints healthPoints2(150); /* has 150 points out of 150 */

	healthPoints1 -= 20; /* now has 80 points out of 100 */
	testResult = testResult && checkHealthPointsValues(healthPoints1, 80, 100);

	healthPoints1 += 100; /* now has 100 points out of 100 */
	testResult = testResult && checkHealthPointsValues(healthPoints1, 100, 100);

	healthPoints1 -= 150; /* now has 0 points out of 100 */
	testResult = testResult && checkHealthPointsValues(healthPoints1, 0, 100);

	healthPoints2 = healthPoints2 - 160; /* now has 0 points out of 150 */
	testResult = testResult && checkHealthPointsValues(healthPoints2, 0, 150);

	healthPoints2 = 160 + healthPoints1; /* now has 100 out of 100 */
	testResult = testResult && checkHealthPointsValues(healthPoints2, 100, 100);

/*
    std::string result;

    HealthPoints hp1 = 1;
    //helperReadHP(hp1, result);
    //REQUIRE(result == "1(1)");

    hp1 += 1;
    //helperReadHP(hp1, result);
   // REQUIRE(result == "1(1)");

   // helperReadHP(hp1 + 1, result);
    //REQUIRE(result == "1(1)");

  //  helperReadHP(1 + hp1, result);
    //REQUIRE(result == "1(1)");

    HealthPoints hp2 = 80085;
   // helperReadHP(hp2, result);
    //REQUIRE(result == "80085(80085)");

    hp2 -= 80000;
   // helperReadHP(hp2, result);
   // REQUIRE(result == "85(80085)");

    hp2 -= 80;
   // helperReadHP(hp2, result);
    //REQUIRE(result == "5(80085)");

    hp2 -= 80;
    //helperReadHP(hp2, result);
   // REQUIRE(result == "0(80085)");

    hp2 -= 1;
  //  helperReadHP(hp2, result);
   // REQUIRE(result == "0(80085)");

    hp2 += 1;
   // helperReadHP(hp2, result);
   // REQUIRE(result == "1(80085)");

    hp2 += 80;
   // helperReadHP(hp2, result);
    //REQUIRE(result == "81(80085)");

    hp2 += 8000;
   // helperReadHP(hp2, result);
   // REQUIRE(result == "8081(80085)");

    hp2 += 80000;
    //helperReadHP(hp2, result);
    //REQUIRE(result == "80085(80085)");

    hp2 -= 3;
    //helperReadHP(hp2, result);
    //REQUIRE(result == "80082(80085)");

    hp2 += 3;
    //helperReadHP(hp2, result);
    //REQUIRE(result == "80085(80085)");

    hp2 -= 80085;
    //helperReadHP(hp2, result);
    //REQUIRE(result == "0(80085)");

    hp1 = hp2 + 100;
   // helperReadHP(hp1, result);
    //REQUIRE(result == "100(80085)");

    hp1 = hp1 - 1;
    //helperReadHP(hp1, result);
    //REQUIRE(result == "99(80085)");

    hp1 = hp1 - 1;
    //helperReadHP(hp1, result);
    //REQUIRE(result == "98(80085)");

    hp1 = hp1 + 1;
    //helperReadHP(hp1, result);
    //REQUIRE(result == "99(80085)");

    hp1 = hp1 + 1;
    //helperReadHP(hp1, result);
    //REQUIRE(result == "100(80085)");

    hp1 = 1 + hp1;
    //helperReadHP(hp1, result);
    //REQUIRE(result == "101(80085)");

    hp1 = 1 + hp1;
    //helperReadHP(hp1, result);
    //REQUIRE(result == "102(80085)");

    hp1 = hp2 + 90000;
    //helperReadHP(hp1, result);
   // REQUIRE(result == "80085(80085)");

    hp1 = 90000 + hp2;
    //helperReadHP(hp1, result);
    //REQUIRE(result == "80085(80085)");

    hp2 = hp1 - 80000;
    //helperReadHP(hp2, result);
    //REQUIRE(result == "85(80085)");

    hp1 = hp2 - 90000;
    //helperReadHP(hp1, result);
   // REQUIRE(result == "0(80085)");

    hp1 = hp2 + (-2);
    //helperReadHP(hp1, result);
    //REQUIRE(result == "83(80085)");

    hp1 = (-84) + hp2;
    //helperReadHP(hp1, result);
    //REQUIRE(result == "1(80085)");


	return testResult;
*/
}

bool testComparisonOperators()
{
	bool testResult = true;
	HealthPoints healthPoints1 = HealthPoints(100); /* has 100 points out of 100 */
	HealthPoints healthPoints2 = 100; /* has 100 points out of 100 */
	bool comparisonResult;

	comparisonResult = (healthPoints1 == healthPoints2); /* returns true */
	testResult = testResult && comparisonResult;

	healthPoints2 = HealthPoints(150); /* has 150 points out of 150 */
	comparisonResult = (healthPoints1 == healthPoints2); /* returns false */
	testResult = testResult && !comparisonResult;

	healthPoints2 -= 50; /* now has 100 points out of 150 */
	comparisonResult = (healthPoints1 == healthPoints2); /* returns true */

	comparisonResult = (healthPoints1 < healthPoints2); /* returns false */
	testResult = testResult && !comparisonResult;

	healthPoints1 -= 50; /* now has 50 points out of 100 */
	comparisonResult = (healthPoints1 < healthPoints2); /* returns true */

	return testResult;
}

bool testOutputOperator()
{
	bool testResult = true;
	std::ostringstream stream;

	HealthPoints healthPoints1 = HealthPoints(100); /* has 100 points out of 100 */
	healthPoints1 -= 50; /* now has 50 points out of 100 */
	stream << healthPoints1; /* stream content is "50(100)" */
	testResult = testResult && (stream.str() == "50(100)");

	HealthPoints healthPoints2 = HealthPoints(150); /* has 1500 points out of 150 */
	healthPoints2 -= 50; /* now has 100 points out of 150 */
	stream << ", " << healthPoints2; /* stream content is "50(100), 100(150)" */
	testResult = testResult && (stream.str() == "50(100), 100(150)");

	return testResult;
}

}
