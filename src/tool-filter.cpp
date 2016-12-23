//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed Nov 30 01:02:57 PST 2016
// Last Modified: Fri Dec  2 03:45:34 PST 2016
// Filename:      tool-filter.cpp
// URL:           https://github.com/craigsapp/minHumdrum/blob/master/src/tool-filter.cpp
// Syntax:        C++11
// vim:           syntax=cpp ts=3 noexpandtab nowrap
//
// Description:   Example of extracting a 2D pitch grid from
//                a score for dissonance analysis.
//

#include "tool-filter.h"

// tools which filter can process:
#include "tool-autobeam.h"
#include "tool-autostem.h"
#include "tool-extract.h"
#include "tool-recip.h"
#include "tool-satb2gs.h"
#include "tool-metlev.h"
#include "tool-myank.h"
#include "tool-transpose.h"
#include "HumRegex.h"

#include <algorithm>
#include <cmath>


using namespace std;

namespace hum {

// START_MERGE


#define RUNTOOL(NAME, INFILE, COMMAND, STATUS)     \
	Tool_##NAME *tool = new Tool_##NAME;            \
	tool->process(COMMAND);                         \
	tool->run(INFILE);                              \
	if (tool->hasError()) {                         \
		status = false;                              \
		tool->getError(cerr);                        \
		delete tool;                                 \
		break;                                       \
	} else if (tool->hasHumdrumText()) {            \
		INFILE.readString(tool->getHumdrumText());   \
	}                                               \
	delete tool;


////////////////////////////////
//
// Tool_filter::Tool_filter -- Set the recognized options for the tool.
//

Tool_filter::Tool_filter(void) {
	define("debug=b", "print debug statement");
}



/////////////////////////////////
//
// Tool_filter::run -- Primary interfaces to the tool.
//

bool Tool_filter::run(const string& indata, ostream& out) {
	HumdrumFile infile(indata);
	bool status = run(infile);
	if (hasAnyText()) {
		getAllText(out);
	} else {
		out << infile;
	}
	return status;
}


bool Tool_filter::run(HumdrumFile& infile, ostream& out) {
	int status = run(infile);
	if (hasAnyText()) {
		getAllText(out);
	} else {
		out << infile;
	}
	return status;
}

//
// In-place processing of file:
//

bool Tool_filter::run(HumdrumFile& infile) {
	initialize(infile);

	bool status = true;
	vector<pair<string, string> > commands;
	getCommandList(commands, infile);
	for (int i=0; i<(int)commands.size(); i++) {
		if (commands[i].first == "autobeam") {
			RUNTOOL(autobeam, infile, commands[i].second, status);
		} else if (commands[i].first == "autostem") {
			RUNTOOL(autostem, infile, commands[i].second, status);
		} else if (commands[i].first == "extract") {
			RUNTOOL(extract, infile, commands[i].second, status);
		} else if (commands[i].first == "metlev") {
			RUNTOOL(metlev, infile, commands[i].second, status);
		} else if (commands[i].first == "satb2gs") {
			RUNTOOL(satb2gs, infile, commands[i].second, status);
		} else if (commands[i].first == "recip") {
			RUNTOOL(recip, infile, commands[i].second, status);
		} else if (commands[i].first == "transpose") {
			RUNTOOL(transpose, infile, commands[i].second, status);
		} else if (commands[i].first == "myank") {
			RUNTOOL(myank, infile, commands[i].second, status);
		}
	}

	// Re-load the text for each line from their tokens in case any
	// updates are needed from token changes.
	infile.createLinesFromTokens();
	return status;
}



//////////////////////////////
//
// Tool_filter::getCommandList --
//

void Tool_filter::getCommandList(vector<pair<string, string> >& commands,
		HumdrumFile& infile) {

	vector<HumdrumLine*> refs = infile.getReferenceRecords();
	pair<string, string> entry;
	string tag = "filter";
	vector<string> clist;
	HumRegex hre;
   if (m_variant.size() > 0) {
		tag += "-";
		tag += m_variant;
	}
	for (int i=0; i<(int)refs.size(); i++) {
		if (refs[i]->getReferenceKey() != tag) {
			continue;
		}
		string command = refs[i]->getReferenceValue();
		hre.split(clist, command, "\\s*\\|\\s*");
		for (int j=0; j<(int)clist.size(); j++) {
			if (hre.search(clist[j], "^\\s*([^\\s]+)")) {
				entry.first  = hre.getMatch(1);
				entry.second = clist[j];
				commands.push_back(entry);
			}
		}
	}
}



//////////////////////////////
//
// Tool_filter::initialize -- extract time signature lines for
//    each **kern spine in file.
//

void Tool_filter::initialize(HumdrumFile& infile) {
	m_debugQ = getBoolean("debug");
}



// END_MERGE

} // end namespace hum


