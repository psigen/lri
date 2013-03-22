//
// HelpFormatterTest.cpp
//
// $Id: //poco/1.4/Util/testsuite/src/HelpFormatterTest.cpp#1 $
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "HelpFormatterTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include <iostream>


using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;


HelpFormatterTest::HelpFormatterTest(const std::string& name): CppUnit::TestCase(name)
{
}


HelpFormatterTest::~HelpFormatterTest()
{
}


void HelpFormatterTest::testHelpFormatter()
{
	OptionSet set;
	set.addOption(
		Option("include-dir", "I", "specify a search path for locating header files")
			.required(false)
			.repeatable(true)
			.argument("path"));
			
	set.addOption(
		Option("library-dir", "L", "specify a search path for locating library files (this option has a very long description)")
			.required(false)
			.repeatable(true)
			.argument("path"));

	set.addOption(
		Option("output", "o", "specify the output file", true)
			.argument("file", true));

	set.addOption(
		Option("verbose", "v")
		.description("enable verbose mode")
		.required(false)
		.repeatable(false));
		
	set.addOption(
		Option("optimize", "O")
		.description("enable optimization")
		.required(false)
		.repeatable(false)
		.argument("level", false));

	HelpFormatter formatter(set);
	formatter.format(std::cout);
	
	formatter.setCommand("cc");
	formatter.format(std::cout);
	
	formatter.setUsage("OPTIONS FILES");
	formatter.setHeader("Lorem ipsum dolor sit amet, consectetuer adipiscing elit. "
		"Vivamus volutpat imperdiet massa. Nulla at ipsum vitae risus facilisis posuere. "
		"Cras convallis, lacus ac vulputate convallis, metus nisl euismod ligula, "
		"ac euismod diam wisi in dolor.\nMauris vitae leo.");
	formatter.setFooter("Cras semper mollis tellus. Mauris eleifend mauris et lorem. "
		"Etiam odio dolor, fermentum quis, mollis nec, sodales sed, tellus. "
		"Quisque consequat orci eu augue. Aliquam ac nibh ac neque hendrerit iaculis.");
	formatter.format(std::cout);
	
	formatter.setUnixStyle(false);
	formatter.format(std::cout);
	
	formatter.setHeader("");
	formatter.setFooter("tab: a\tb\tcde\tf\n\ta\n\t\tb");
	formatter.format(std::cout);
}


void HelpFormatterTest::setUp()
{
}


void HelpFormatterTest::tearDown()
{
}


CppUnit::Test* HelpFormatterTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("HelpFormatterTest");

	CppUnit_addTest(pSuite, HelpFormatterTest, testHelpFormatter);

	return pSuite;
}
