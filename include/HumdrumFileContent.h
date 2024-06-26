//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Mon Aug 17 02:39:28 PDT 2015
// Last Modified: Fri Dec  6 19:27:27 PST 2019
// Filename:      HumdrumFileContent.h
// URL:           https://github.com/craigsapp/humlib/blob/master/include/HumdrumFileContent.h
// Syntax:        C++11; humlib
// vim:           syntax=cpp ts=3 noexpandtab nowrap
//
// Description:   Used to add content analysis to HumdrumFileStructure class,
//                and do other higher-level processing of Humdrum data.
//

#ifndef _HUMDRUMFILECONTENT_H_INCLUDED
#define _HUMDRUMFILECONTENT_H_INCLUDED

#include "HumdrumFileStructure.h"

#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

namespace hum {

// START_MERGE

class HumdrumFileContent : public HumdrumFileStructure {
	public:
		       HumdrumFileContent         (void);
		       HumdrumFileContent         (const std::string& filename);
		       HumdrumFileContent         (std::istream& contents);
		      ~HumdrumFileContent         ();

		bool   analyzeSlurs               (void);  // in src/HumdrumFileContents-slur.cpp
		bool   analyzeBeams               (void);  // in src/HumdrumFileContents-beam.cpp
		bool   analyzePhrasings           (void);
		bool   analyzeTextRepetition      (void);
		bool   analyzeKernTies            (void);
		bool   analyzeAccidentals         (void);
		bool   analyzeKernAccidentals     (const std::string& dataType = "**kern");
		bool   analyzeMensAccidentals     (void);
		bool   analyzeRScale              (void);

		// in HumdrumFileContent-hand.cpp
		bool   doHandAnalysis             (bool attacksOnlyQ = false);
		bool   doHandAnalysis             (HTp startSpine, bool attacksOnlyQ = false);

		// in HumdrumFileContent-kern.cpp
		std::vector<int> getTrackToKernIndex (void);

		// in HumdrumFileContent-midi.cpp
		void fillMidiInfo(std::vector<std::vector<std::vector<std::pair<HTp, int>>>>& trackMidi);
		void processStrandNotesForMidi(HTp sstart, HTp send, std::vector<std::vector<std::pair<HTp, int>>>& trackInfo);

		// in HumdrumFileContent-rest.cpp
		void  analyzeRestPositions                  (void);
		void  assignImplicitVerticalRestPositions   (HTp kernstart);
		void  checkForExplicitVerticalRestPositions (void);

		// in HumdrumFileContent-stem.cpp
		bool analyzeKernStemLengths       (void);

		// in HumdrumFileContent-metlev.cpp
		void  getMetricLevels             (std::vector<double>& output, int track = 0,
		                                   double undefined = NAN);
		// in HumdrumFileContent-timesig.cpp
		void  getTimeSigs                 (std::vector<std::pair<int, HumNum> >& output,
		                                   int track = 0);

		template <class DATATYPE>
		bool   prependDataSpine           (std::vector<DATATYPE> data,
		                                   const std::string& null = ".",
		                                   const std::string& exinterp = "**data",
		                                   bool recalcLine = true);

		template <class DATATYPE>
		bool   appendDataSpine            (std::vector<DATATYPE> data,
		                                   const std::string& null = ".",
		                                   const std::string& exinterp = "**data",
		                                   bool recalcLine = true);

		template <class DATATYPE>
		bool   insertDataSpineBefore      (int nexttrack,
		                                   std::vector<DATATYPE> data,
		                                   const std::string& null = ".",
		                                   const std::string& exinterp = "**data",
		                                   bool recalcLine = true);

		template <class DATATYPE>
		bool   insertDataSpineAfter       (int prevtrack,
		                                   std::vector<DATATYPE> data,
		                                   const std::string& null = ".",
		                                   const std::string& exinterp = "**data",
		                                   bool recalcLine = true);

		// in HumdrumFileContent-ottava.cpp
		void   analyzeOttavas             (void);

		// in HumdrumFileContent-note.cpp
		void   analyzeCrossStaffStemDirections (void);
		void   analyzeCrossStaffStemDirections (HTp kernstart);
		int    getNoteCount               (void);
		int    hasPickup                  (void);

		// in HumdrumFileContent-barline.cpp
		void   analyzeBarlines            (void);
		bool   hasDifferentBarlines       (void);
		bool   hasDataStraddle            (int line);

	protected:

		bool   analyzeKernPhrasings       (HTp spinestart,
		                                   std::vector<HTp>& linkstarts,
		                                   std::vector<HTp>& linkends,
		                                   std::vector<std::pair<HTp, HTp>>& labels,
		                                   std::vector<int>& endings,
		                                   const std::string& linksig);
		bool   analyzeKernTies            (std::vector<std::pair<HTp, int>>& linkedtiestarts,
		                                   std::vector<std::pair<HTp, int>>& linkedtieends,
		                                   std::string& linkSignifier);
		void   fillKeySignature           (std::vector<int>& states,
		                                   const std::string& keysig);
		void   resetDiatonicStatesWithKeySignature(std::vector<int>& states,
				                             std::vector<int>& signature);

		bool   analyzeKernPhrasings       (void);

		// Slur analysis functions (defined in src/HumdrumFileContents-slur.cpp):
		bool   analyzeMensSlurs           (void);
		bool   analyzeKernSlurs           (void);
		void   createLinkedSlurs          (std::vector<HTp>& linkstarts, std::vector<HTp>& linkends);
		bool   isLinkedSlurEnd            (HTp token, int index, const std::string& pattern);
		bool   isLinkedSlurBegin          (HTp token, int index, const std::string& pattern);
		void   linkSlurEndpoints          (HTp slurstart, HTp slurend);
		bool   analyzeKernSlurs           (HTp spinestart, std::vector<HTp>& slurstarts,
		                                   std::vector<HTp>& slurends,
		                                   std::vector<std::pair<HTp, HTp>>& labels,
		                                   std::vector<int>& endings,
		                                   const std::string& linksig = "");

		// Beam analysis functions (defined in src/HumdrumFileContents-beam.cpp):
		bool   analyzeMensBeams           (void);
		bool   analyzeKernBeams           (void);
		void   createLinkedBeams          (std::vector<HTp>& linkstarts, std::vector<HTp>& linkends);
		bool   isLinkedBeamEnd            (HTp token, int index, const std::string& pattern);
		bool   isLinkedBeamBegin          (HTp token, int index, const std::string& pattern);
		void   linkBeamEndpoints          (HTp beamstart, HTp beamend);
		void   markBeamSpanMembers        (HTp beamstart, HTp beamend);
		bool   analyzeKernBeams           (HTp spinestart, std::vector<HTp>& beamstarts,
		                                   std::vector<HTp>& beamends,
		                                   std::vector<std::pair<HTp, HTp>>& labels,
		                                   std::vector<int>& endings,
		                                   const std::string& linksig = "");

		// Analytic phrase markers:
		void    linkPhraseEndpoints       (HTp phrasestart, HTp phraseend);
		void    linkTieEndpoints          (HTp tiestart, int startindex,
		                                   HTp tieend, int endindex);
		bool    isLinkedPhraseBegin       (HTp token, int index, const std::string& pattern);
		bool    isLinkedPhraseEnd         (HTp token, int index, const std::string& pattern);
		void    createLinkedPhrasings     (std::vector<HTp>& linkstarts, std::vector<HTp>& linkends);

		// Rests:
		void    assignVerticalRestPosition(HTp first, HTp second, int baseline);
		int     getRestPositionAboveNotes (HTp rest, std::vector<int>& vpos);
		int     getRestPositionBelowNotes (HTp rest, std::vector<int>& vpos);
		void    setRestOnCenterStaffLine  (HTp rest, int baseline);
		bool    checkRestForVerticalPositioning(HTp rest, int baseline);

		// Stem lengths:
		bool    analyzeKernStemLengths    (HTp stok, HTp etok, std::vector<std::vector<int>>& centerlines);
		void    checkCrossStaffStems      (HTp token, std::string& above, std::string& below);
		void    checkDataForCrossStaffStems(HTp token, std::string& above, std::string& below);
		void    prepareStaffAboveNoteStems (HTp token);
		void    prepareStaffBelowNoteStems (HTp token);

		void    getBaselines              (std::vector<std::vector<int>>& centerlines);
		void    createLinkedTies          (std::vector<std::pair<HTp, int>>& starts,
		                                   std::vector<std::pair<HTp, int>>& ends);
};


//
// Templates:
//


//////////////////////////////
//
// HumdrumFileContent::prependDataSpine -- prepend a data spine
//     to the file.  Returns true if successful; false otherwise.
//
//     data == numeric or string data to print
//     null == if the data is converted to a string is equal to this
//             string then set the data spine content to a null token, ".".
//             default is ".".
//     exinterp == the exterp string to use.  Default is "**data".
//     recalcLine == boolean for whether or not to recalculate line string.
//                   Default is true;
//

template <class DATATYPE>
bool HumdrumFileContent::prependDataSpine(std::vector<DATATYPE> data,
		const std::string& null, const std::string& exinterp, bool recalcLine) {

	if ((int)data.size() != getLineCount()) {
		return false;
	}

	std::string ex;
	if (exinterp.find("**") == 0) {
		ex = exinterp;
	} else if (exinterp.find("*") == 0) {
		ex = "*" + exinterp;
	} else {
		ex = "**" + exinterp;
	}
	if (ex.size() <= 2) {
		ex += "data";
	}

	std::stringstream ss;
	HumdrumFileContent& infile = *this;
	HLp line;
	for (int i=0; i<infile.getLineCount(); i++) {
		line = infile.getLine(i);
		if (!line->hasSpines()) {
			continue;
		}
		if (line->isExclusive()) {
			line->insertToken(0, ex);
		} else if (line->isTerminator()) {
			line->insertToken(0, "*-");
		} else if (line->isInterpretation()) {
			line->insertToken(0, "*");
		} else if (line->isLocalComment()) {
			line->insertToken(0, "!");
		} else if (line->isBarline()) {
			line->insertToken(0, (std::string)*infile.token(i, 0));
		} else if (line->isData()) {
			ss.str(std::string());
			ss << data[i];
			if (ss.str() == null) {
				line->insertToken(0, ".");
			} else if (ss.str() == "") {
				line->insertToken(0, ".");
			} else {
				line->insertToken(0, ss.str());
			}
		} else{
			std::cerr << "!!strange error for line " << i+1 << ":\t" << line << std::endl;
		}
		if (recalcLine) {
			line->createLineFromTokens();
		}
	}
	return true;
}



//////////////////////////////
//
// HumdrumFileContent::appendDataSpine -- prepend a data spine
//     to the file.  Returns true if successful; false otherwise.
//
//     data == numeric or string data to print
//     null == if the data is converted to a string is equal to this
//             string then set the data spine content to a null token, ".".
//             default is ".".
//     exinterp == the exterp string to use.  Default is "**data".
//     recalcLine == boolean for whether or not to recalculate line string.
//                   Default is true;
//

template <class DATATYPE>
bool HumdrumFileContent::appendDataSpine(std::vector<DATATYPE> data,
		const std::string& null, const std::string& exinterp, bool recalcLine) {

	if ((int)data.size() != getLineCount()) {
		std::cerr << "DATA SIZE DOES NOT MATCH GETLINECOUNT " << std::endl;
		std::cerr << "DATA SIZE " << data.size() << "\tLINECOUNT ";
		std::cerr  << getLineCount() << std::endl;
		return false;
	}

	std::string ex;
	if (exinterp.find("**") == 0) {
		ex = exinterp;
	} else if (exinterp.find("*") == 0) {
		ex = "*" + exinterp;
	} else {
		ex = "**" + exinterp;
	}
	if (ex.size() <= 2) {
		ex += "data";
	}

	std::stringstream ss;
	HumdrumFileContent& infile = *this;
	HLp line;
	for (int i=0; i<infile.getLineCount(); i++) {
		line = infile.getLine(i);
		if (!line->hasSpines()) {
			continue;
		}
		if (line->isExclusive()) {
			line->appendToken(ex);
		} else if (line->isTerminator()) {
			line->appendToken("*-");
		} else if (line->isInterpretation()) {
			line->appendToken("*");
		} else if (line->isLocalComment()) {
			line->appendToken("!");
		} else if (line->isBarline()) {
			line->appendToken((std::string)*infile.token(i, 0));
		} else if (line->isData()) {
			ss.str(std::string());
			ss << data[i];
			if (ss.str() == null) {
				line->appendToken(".");
			} else if (ss.str() == "") {
				line->appendToken(".");
			} else {
				line->appendToken(ss.str());
			}
		} else{
			std::cerr << "!!strange error for line " << i+1 << ":\t" << line << std::endl;
		}
		if (recalcLine) {
			line->createLineFromTokens();
		}
	}
	return true;
}



//////////////////////////////
//
// HumdrumFileContent::insertDataSpineBefore -- prepend a data spine
//     to the file before the given spine.  Returns true if successful;
//     false otherwise.
//
//     nexttrack == track number to insert before.
//     data == numeric or string data to print
//     null == if the data is converted to a string is equal to this
//             string then set the data spine content to a null token, ".".
//             default is ".".
//     exinterp == the exterp string to use.  Default is "**data".
//     recalcLine == boolean for whether or not to recalculate line string.
//                   Default is true;
//

template <class DATATYPE>
bool HumdrumFileContent::insertDataSpineBefore(int nexttrack,
		std::vector<DATATYPE> data, const std::string& null, const std::string& exinterp,
		bool recalcLine) {

	if ((int)data.size() != getLineCount()) {
		std::cerr << "DATA SIZE DOES NOT MATCH GETLINECOUNT " << std::endl;
		std::cerr << "DATA SIZE " << data.size() << "\tLINECOUNT ";
		std::cerr  << getLineCount() << std::endl;
		return false;
	}

	std::string ex;
	if (exinterp.find("**") == 0) {
		ex = exinterp;
	} else if (exinterp.find("*") == 0) {
		ex = "*" + exinterp;
	} else {
		ex = "**" + exinterp;
	}
	if (ex.size() <= 2) {
		ex += "data";
	}

	std::stringstream ss;
	HumdrumFileContent& infile = *this;
	HLp line;
	int insertionField = -1;
	int track;
	for (int i=0; i<infile.getLineCount(); i++) {
		line = infile.getLine(i);
		if (!line->hasSpines()) {
			continue;
		}
		insertionField = -1;
		for (int j=0; j<line->getFieldCount(); j++) {
			track = line->token(j)->getTrack();
			if (track != nexttrack) {
				continue;
			}
			insertionField = j;
			break;
		}
		if (insertionField < 0) {
			return false;
		}

		if (line->isExclusive()) {
			line->insertToken(insertionField, ex);
		} else if (line->isTerminator()) {
			line->insertToken(insertionField, "*-");
		} else if (line->isInterpretation()) {
			line->insertToken(insertionField, "*");
		} else if (line->isLocalComment()) {
			line->insertToken(insertionField, "!");
		} else if (line->isBarline()) {
			line->insertToken(insertionField, (std::string)*infile.token(i, 0));
		} else if (line->isData()) {
			ss.str(std::string());
			ss << data[i];
			if (ss.str() == null) {
				line->insertToken(insertionField, ".");
			} else if (ss.str() == "") {
				line->insertToken(insertionField, ".");
			} else {
				line->insertToken(insertionField, ss.str());
			}
		} else{
			std::cerr << "!!strange error for line " << i+1 << ":\t" << line << std::endl;
		}
		if (recalcLine) {
			line->createLineFromTokens();
		}
	}
	return true;
}



//////////////////////////////
//
// HumdrumFileContent::insertDataSpineAfter -- appen a data spine
//     to the file after the given spine.  Returns true if successful;
//     false otherwise.
//
//     prevtrack == track number to insert after.
//     data == numeric or string data to print
//     null == if the data is converted to a string is equal to this
//             string then set the data spine content to a null token, ".".
//             default is ".".
//     exinterp == the exterp string to use.  Default is "**data".
//     recalcLine == boolean for whether or not to recalculate line string.
//                   Default is true;
//

template <class DATATYPE>
bool HumdrumFileContent::insertDataSpineAfter(int prevtrack,
		std::vector<DATATYPE> data, const std::string& null, const std::string& exinterp,
		bool recalcLine) {

	if ((int)data.size() != getLineCount()) {
		std::cerr << "DATA SIZE DOES NOT MATCH GETLINECOUNT " << std::endl;
		std::cerr << "DATA SIZE " << data.size() << "\tLINECOUNT ";
		std::cerr  << getLineCount() << std::endl;
		return false;
	}

	std::string ex;
	if (exinterp.find("**") == 0) {
		ex = exinterp;
	} else if (exinterp.find("*") == 0) {
		ex = "*" + exinterp;
	} else {
		ex = "**" + exinterp;
	}
	if (ex.size() <= 2) {
		ex += "data";
	}

	std::stringstream ss;
	HumdrumFileContent& infile = *this;
	HLp line;
	int insertionField = -1;
	int track;
	for (int i=0; i<infile.getLineCount(); i++) {
		line = infile.getLine(i);
		if (!line->hasSpines()) {
			continue;
		}
		insertionField = -1;
		for (int j = line->getFieldCount() - 1; j >= 0; j--) {
			track = line->token(j)->getTrack();
			if (track != prevtrack) {
				continue;
			}
			insertionField = j;
			break;
		}
		insertionField++;
		if (insertionField < 0) {
			return false;
		}

		if (line->isExclusive()) {
			line->insertToken(insertionField, ex);
		} else if (line->isTerminator()) {
			line->insertToken(insertionField, "*-");
		} else if (line->isInterpretation()) {
			line->insertToken(insertionField, "*");
		} else if (line->isLocalComment()) {
			line->insertToken(insertionField, "!");
		} else if (line->isBarline()) {
			line->insertToken(insertionField, (std::string)*infile.token(i, 0));
		} else if (line->isData()) {
			ss.str(std::string());
			ss << data[i];
			if (ss.str() == null) {
				line->insertToken(insertionField, ".");
			} else if (ss.str() == "") {
				line->insertToken(insertionField, ".");
			} else {
				line->insertToken(insertionField, ss.str());
			}
		} else{
			std::cerr << "!!strange error for line " << i+1 << ":\t" << line << std::endl;
		}
		if (recalcLine) {
			line->createLineFromTokens();
		}
	}
	return true;
}


// END_MERGE

} // end namespace hum

#endif /* _HUMDRUMFILECONTENT_H_INCLUDED */



