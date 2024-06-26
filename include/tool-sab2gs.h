//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Mon Apr  1 01:06:00 PDT 2024
// Last Modified: Mon Apr  1 23:38:33 PDT 2024
// Filename:      tool-sab2gs.h
// URL:           https://github.com/craigsapp/humlib/blob/master/include/tool-sab2gs.h
// Syntax:        C++11; humlib
// vim:           ts=3 noexpandtab
//
// Description:   Convert 3-staff single-voice music into 2-staff Grand Staff layout.
//

#ifndef _TOOL_SAB2GS_H
#define _TOOL_SAB2GS_H

#include "HumTool.h"
#include "HumdrumFile.h"

#include <ostream>
#include <string>
#include <vector>

namespace hum {

// START_MERGE

class Tool_sab2gs : public HumTool {
	public:
		         Tool_sab2gs      (void);
		        ~Tool_sab2gs      () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void    processFile        (HumdrumFile& infile);
		void    initialize         (void);

		void    adjustMiddleVoice  (HTp spineStart);
		void    printGrandStaff    (HumdrumFile& infile, std::vector<HTp>& starts);
		std::string hasBelowMarker(HumdrumFile& infile);

		void    printReducedLine   (HumdrumFile& infile, int index, std::vector<int>& ktracks);
		void    printSpineMerge    (HumdrumFile& infile, int index, std::vector<int>& ktracks);
		void    printSpineSplit    (HumdrumFile& infile, int index, std::vector<int>& ktracks);
		void    printSwappedLine   (HumdrumFile& infile, int index, std::vector<int>& ktracks);

	private:
		bool    m_hasCrossStaff = false;   // Middle voice has notes/rests on bottom staff
		bool    m_hasBelowMarker = false;  // Input data has RDF**kern down marker
		std::string  m_belowMarker = "<";       // RDF**kern marker for staff down
		bool    m_downQ = false;           // Used only *down/*Xdown for staff changes


};

// END_MERGE

} // end namespace hum

#endif /* _TOOL_SAB2GS_H */



