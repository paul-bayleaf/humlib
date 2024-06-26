//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Mon Aug  7 20:17:53 EDT 2017
// Last Modified: Mon Aug  7 20:17:56 EDT 2017
// Filename:      tool-hproof.h
// URL:           https://github.com/craigsapp/humlib/blob/master/include/tool-hproof.h
// Syntax:        C++11; humlib
// vim:           syntax=cpp ts=3 noexpandtab nowrap
//
// Description:   Interface for hproof tool.
//

#ifndef _TOOL_HPROOF_H_INCLUDED
#define _TOOL_HPROOF_H_INCLUDED

#include "HumTool.h"
#include "HumdrumFile.h"

#include <ostream>
#include <string>
#include <vector>

namespace hum {

// START_MERGE

class Tool_hproof : public HumTool {
	public:
		      Tool_hproof      (void);
		     ~Tool_hproof      () {};

		bool  run              (HumdrumFileSet& infiles);
		bool  run              (HumdrumFile& infile);
		bool  run              (const std::string& indata, std::ostream& out);
		bool  run              (HumdrumFile& infile, std::ostream& out);

	protected:
		void  markNonChordTones(HumdrumFile& infile);
		void  processHarmSpine (HumdrumFile& infile, HTp hstart);
		void  markNotesInRange (HumdrumFile& infile, HTp ctoken, HTp ntoken, const std::string& key);
		void  markHarmonicTones(HTp tok, std::vector<int>& cts);
		void  getNewKey        (HTp token, HTp ntoken, std::string& key);

	private:
		std::vector<HTp> m_kernspines;

};


// END_MERGE

} // end namespace hum

#endif /* _TOOL_HPROOF_H_INCLUDED */



