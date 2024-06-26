//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Mon Nov 28 08:55:15 PST 2016
// Last Modified: Mon Nov 28 08:55:38 PST 2016
// Filename:      tool-recip.h
// URL:           https://github.com/craigsapp/humlib/blob/master/include/tool-recip.h
// Syntax:        C++11; humlib
// vim:           syntax=cpp ts=3 noexpandtab nowrap
//
// Description:   Interface for recip tool.
//

#ifndef _TOOL_RECIP_H_INCLUDED
#define _TOOL_RECIP_H_INCLUDED

#include "HumTool.h"
#include "HumdrumFile.h"

#include <ostream>
#include <string>
#include <vector>

namespace hum {

// START_MERGE

class Tool_recip : public HumTool {
	public:
		      Tool_recip               (void);
		     ~Tool_recip               () {};

		bool  run                      (HumdrumFileSet& infiles);
		bool  run                      (HumdrumFile& infile);
		bool  run                      (const std::string& indata, std::ostream& out);
		bool  run                      (HumdrumFile& infile, std::ostream& out);

	protected:
		void  initialize               (HumdrumFile& infile);
		void  replaceKernWithRecip     (HumdrumFile& infile);
		void  doCompositeAnalysis      (HumdrumFile& infile);
		void  insertAnalysisSpines     (HumdrumFile& infile, HumdrumFile& cfile);

	private:
		std::vector<HTp> m_kernspines;
		bool        m_graceQ = true;
		std::string      m_exinterp = "**recip";
		std::string      m_kernpitch = "e";

};


// END_MERGE

} // end namespace hum

#endif /* _TOOL_RECIP_H_INCLUDED */



