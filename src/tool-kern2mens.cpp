//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sat May  5 21:06:29 PDT 2018
// Last Modified: Sat May  5 21:06:32 PDT 2018
// Filename:      tool-kern2mens.cpp
// URL:           https://github.com/craigsapp/humlib/blob/master/src/tool-kern2mens.cpp
// Syntax:        C++11
// vim:           ts=3 noexpandtab
//
// Description:   Interface for fixing early-music MusicXML import where a tied note over a barline
//                is represented as an invisible rest.  This occurs in MusicXML output from Sibelius.
//

#include "tool-kern2mens.h"
#include "Convert.h"
#include "HumRegex.h"

using namespace std;

namespace hum {

// START_MERGE


/////////////////////////////////
//
// Tool_kern2mens::Tool_kern2mens -- Set the recognized options for the tool.
//

Tool_kern2mens::Tool_kern2mens(void) {
	// add options here
}



/////////////////////////////////
//
// Tool_kern2mens::run -- Do the main work of the tool.
//

bool Tool_kern2mens::run(const string& indata, ostream& out) {
	HumdrumFile infile(indata);
	bool status = run(infile);
	if (hasAnyText()) {
		getAllText(out);
	} else {
		out << infile;
	}
	return status;
}


bool Tool_kern2mens::run(HumdrumFile& infile, ostream& out) {
	bool status = run(infile);
	if (hasAnyText()) {
		getAllText(out);
	} else {
		out << infile;
	}
	return status;
}


bool Tool_kern2mens::run(HumdrumFile& infile) {
	convertToMens(infile);
	return true;
}



//////////////////////////////
//
// Tool_kern2mens::convertToMens -- 
//

void Tool_kern2mens::convertToMens(HumdrumFile& infile) {
	for (int i=0; i<infile.getLineCount(); i++) {
		if (infile[i].isBarline()) {
			continue;
		}
		if (!infile[i].hasSpines()) {
			m_humdrum_text << infile[i] << "\n";
			continue;
		}
		for (int j=0; j<infile[i].getFieldCount(); j++) {
			HTp token = infile.token(i, j);
			m_humdrum_text << convertKernTokenToMens(token);
			if (j < infile[i].getFieldCount() - 1) {
				m_humdrum_text << "\t";
			}
		}
		m_humdrum_text << "\n";
	}
}



//////////////////////////////
//
// Tool_kern2mens::convertKernTokenToMens --
//

string Tool_kern2mens::convertKernTokenToMens(HTp token) {
	string data;
	HumRegex hre;
	if (!token->isKern()) {
		return *token;
	}
	if (token->isNull()) {
		return *token;
	}
	if (token->isExclusiveInterpretation()) {
		return "**mens";;
	}
	if (!token->isData()) {
		return *token;
	}
	if (token->isSecondaryTiedNote()) {
		return ".";
	}
	data = *token;
	HumNum dur;
	if (token->find("[") != std::string::npos) {
		dur = token->getTiedDuration();
		hre.replaceDestructive(data, "", "\\[");
	} else {
		dur = token->getDuration();
	}
	string rhythm = Convert::durationToRecip(dur);
	hre.replaceDestructive(data, rhythm, "\\d+\\.*");
	hre.replaceDestructive(data, "X", "000");
	hre.replaceDestructive(data, "L", "00");
	hre.replaceDestructive(data, "S", "0");
	hre.replaceDestructive(data, "s", "1");
	hre.replaceDestructive(data, "M", "2");
	hre.replaceDestructive(data, "m", "4");
	hre.replaceDestructive(data, "U", "8");
	hre.replaceDestructive(data, "u", "16");
	hre.replaceDestructive(data, ":", "\\.");
	return data;
}



// END_MERGE

} // end namespace hum


