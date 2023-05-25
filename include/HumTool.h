//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Mon Nov 28 08:55:15 PST 2016
// Last Modified: Mon Nov 28 08:55:38 PST 2016
// Filename:      HumTool.h
// URL:           https://github.com/craigsapp/humlib/blob/master/include/HumTool.h
// Syntax:        C++11; humlib
// vim:           syntax=cpp ts=3 noexpandtab nowrap
//
// Description:   Common interface for Humdrum tools.
//

#ifndef _HUMTOOL_H_INCLUDED
#define _HUMTOOL_H_INCLUDED

#include "Options.h"
#include "HumdrumFileSet.h"

#include <sstream>
#include <string>

namespace hum {

// START_MERGE

class HumTool : public Options {
	public:
		              HumTool         (void);
		virtual      ~HumTool         ();

		void          clearOutput     (void);

		bool          hasAnyText      (void);
		std::string   getAllText      (void);
		ostream&      getAllText      (ostream& out);

		bool          hasHumdrumText  (void);
		std::string   getHumdrumText  (void);
		ostream&      getHumdrumText  (ostream& out);
		void          suppressHumdrumFileOutput(void);

		bool          hasJsonText     (void);
		std::string   getJsonText     (void);
		ostream&      getJsonText     (ostream& out);

		bool          hasFreeText     (void);
		std::string   getFreeText     (void);
		ostream&      getFreeText     (ostream& out);

		bool          hasWarning      (void);
		std::string   getWarning      (void);
		ostream&      getWarning      (ostream& out);

		bool          hasError        (void);
		std::string   getError        (void);
		ostream&      getError        (ostream& out);
		void          setError        (const string& message);

		virtual void  finally         (void) { };

	protected:
		std::stringstream m_humdrum_text;  // output text in Humdrum syntax.
		std::stringstream m_json_text;     // output text in JSON syntax.
		std::stringstream m_free_text;     // output for plain text content.
	  	std::stringstream m_warning_text;  // output for warning messages;
	  	std::stringstream m_error_text;    // output for error messages;

		bool m_suppress = false;

};


///////////////////////////////////////////////////////////////////////////
//
// common command-line Interfaces
//

//////////////////////////////
//
// BASIC_INTERFACE -- Expects one Humdurm file, either from the
//    first command-line argument (left over after options have been
//    parsed out), or from standard input.
//
// function call that the interface must implement:
//  .run(HumdrumFile& infile, ostream& out)
//
//

#define BASIC_INTERFACE(CLASS)                         \
int main(int argc, char** argv) {                      \
	hum::CLASS interface;                               \
	if (!interface.process(argc, argv)) {               \
		interface.getError(std::cerr);                   \
		return -1;                                       \
	}                                                   \
	hum::HumdrumFile infile;                            \
	if (interface.getArgCount() > 0) {                  \
		infile.readNoRhythm(interface.getArgument(1));   \
	} else {                                            \
		infile.readNoRhythm(std::cin);                   \
	}                                                   \
	int status = interface.run(infile, std::cout);      \
	if (interface.hasWarning()) {                       \
		interface.getWarning(std::cerr);                 \
		return 0;                                        \
	}                                                   \
	if (interface.hasError()) {                         \
		interface.getError(std::cerr);                   \
		return -1;                                       \
	}                                                   \
	interface.finally();                                \
	return !status;                                     \
}



//////////////////////////////
//
// STREAM_INTERFACE -- Use HumdrumFileStream (low-memory
//    usage implementation).
//

#define STREAM_INTERFACE(CLASS)                                            \
int main(int argc, char** argv) {                                          \
	hum::CLASS interface;                                                   \
	if (!interface.process(argc, argv)) {                                   \
		interface.getError(std::cerr);                                       \
		return -1;                                                           \
	}                                                                       \
	hum::HumdrumFileStream instream(static_cast<hum::Options&>(interface)); \
	hum::HumdrumFileSet infiles;                                            \
	bool status = true;                                                     \
	while (instream.readSingleSegment(infiles)) {                           \
		status &= interface.run(infiles);                                    \
		if (interface.hasWarning()) {                                        \
			interface.getWarning(std::cerr);                                  \
		}                                                                    \
		if (interface.hasAnyText()) {                                        \
		   interface.getAllText(std::cout);                                  \
		}                                                                    \
		if (interface.hasError()) {                                          \
			interface.getError(std::cerr);                                    \
         return -1;                                                        \
		}                                                                    \
		if (!interface.hasAnyText()) {                                       \
			for (int i=0; i<infiles.getCount(); i++) {                        \
				cout << infiles[i];                                            \
			}                                                                 \
		}                                                                    \
		interface.clearOutput();                                             \
	}                                                                       \
	interface.finally();                                                    \
	return !status;                                                         \
}



//////////////////////////////
//
// RAW_STREAM_INTERFACE -- Use HumdrumFileStream but send the
//    HumdrumFileStream object to the filter rather than individual
//    Humdrum files.
//

#define RAW_STREAM_INTERFACE(CLASS)                                        \
int main(int argc, char** argv) {                                          \
	hum::CLASS interface;                                                   \
	if (!interface.process(argc, argv)) {                                   \
		interface.getError(std::cerr);                                       \
		return -1;                                                           \
	}                                                                       \
	hum::HumdrumFileStream instream(static_cast<hum::Options&>(interface)); \
	bool status = interface.run(instream);                                  \
	if (interface.hasWarning()) {                                           \
		interface.getWarning(std::cerr);                                     \
	}                                                                       \
	if (interface.hasAnyText()) {                                           \
	   interface.getAllText(std::cout);                                     \
	}                                                                       \
	if (interface.hasError()) {                                             \
		interface.getError(std::cerr);                                       \
        return -1;                                                         \
	}                                                                       \
	interface.finally();                                                    \
	interface.clearOutput();                                                \
	return !status;                                                         \
}



//////////////////////////////
//
// SET_INTERFACE -- Use HumdrumFileSet (multiple file high-memory
//    usage implementation).
//

#define SET_INTERFACE(CLASS)                                               \
int main(int argc, char** argv) {                                          \
	hum::CLASS interface;                                                   \
	if (!interface.process(argc, argv)) {                                   \
		interface.getError(std::cerr);                                       \
		return -1;                                                           \
	}                                                                       \
	hum::HumdrumFileStream instream(static_cast<hum::Options&>(interface)); \
	hum::HumdrumFileSet infiles;                                            \
	instream.read(infiles);                                                 \
	bool status = interface.run(infiles);                                   \
	if (interface.hasWarning()) {                                           \
		interface.getWarning(std::cerr);                                     \
	}                                                                       \
	if (interface.hasAnyText()) {                                           \
	   interface.getAllText(std::cout);                                     \
	}                                                                       \
	if (interface.hasError()) {                                             \
		interface.getError(std::cerr);                                       \
        return -1;                                                         \
	}                                                                       \
	if (!interface.hasAnyText()) {                                          \
		for (int i=0; i<infiles.getCount(); i++) {                           \
			std::cout << infiles[i];                                          \
		}                                                                    \
	}                                                                       \
	interface.finally();                                                    \
	interface.clearOutput();                                                \
	return !status;                                                         \
}


// END_MERGE

} // end namespace hum

#endif /* _HUMTOOL_H_INCLUDED */



