#define BOOST_TEST_MODULE date_test
//#define BOOST_TEST_MAIN
//#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include "metalicensor/generator/license-generator.h"
#include "metalicensor/utils/build_properties.hpp"
#include "metalicensor/api/license++.h"
#include "metalicensor/ini/SimpleIni.h"
#include "generate.h"

namespace fs = boost::filesystem;
using namespace license;
using namespace std;

BOOST_AUTO_TEST_CASE( license_not_expired ) {
	const string licLocation(METALICENSOR_TEST_OUT_DIR "/not_expired.lic");
	vector<string> extraArgs;
	extraArgs.push_back("-e");
	extraArgs.push_back("2050-10-10");
	generate_license(licLocation, extraArgs);
	LicenseInfo license;
	LicenseLocation licenseLocation;
	licenseLocation.openFileNearModule = false;
	licenseLocation.licenseFileLocation = licLocation.c_str();
	licenseLocation.environmentVariableName = "";
	EVENT_TYPE result = acquire_license("TEST", licenseLocation, &license);
	BOOST_CHECK_EQUAL(result, LICENSE_OK);
	BOOST_CHECK_EQUAL(license.has_expiry, true);
	BOOST_CHECK_EQUAL(license.linked_to_pc, false);
}

BOOST_AUTO_TEST_CASE( license_expired ) {
	const string licLocation(METALICENSOR_TEST_OUT_DIR "/expired.lic");
	vector<string> extraArgs;
	extraArgs.push_back("-e");
	extraArgs.push_back("2013-10-10");
	generate_license(licLocation, extraArgs);
	LicenseInfo license;
	LicenseLocation licenseLocation;
	licenseLocation.openFileNearModule = false;
	licenseLocation.licenseFileLocation = licLocation.c_str();
	licenseLocation.environmentVariableName = "";
	EVENT_TYPE result = acquire_license("TEST", licenseLocation, &license);
	BOOST_CHECK_EQUAL(result, PRODUCT_EXPIRED);
	BOOST_CHECK_EQUAL(license.has_expiry, true);
	BOOST_CHECK_EQUAL(license.linked_to_pc, false);
}
