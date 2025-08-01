//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sat Aug  8 12:24:49 PDT 2015
// Last Modified: Wed Jul 23 07:00:37 CEST 2025
// Filename:      min/humlib.h
// URL:           https://github.com/craigsapp/humlib/blob/master/min/humlib.h
// Syntax:        C++11
// vim:           ts=3
//
// Description:   Include file for humlib library.
//
/*
https://github.com/craigsapp/humlib
Copyright (c) 2015-2021 Craig Stuart Sapp
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   and the following disclaimer in the documentation and/or other materials
   provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef _HUMLIB_H_INCLUDED
#define _HUMLIB_H_INCLUDED

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstdarg>
#include <cstring>
#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <locale>
#include <map>
#include <numeric>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ends;
using std::ifstream;
using std::invalid_argument;
using std::istream;
using std::istreambuf_iterator;
using std::list;
using std::map;
using std::ostream;
using std::pair;
using std::regex;
using std::set;
using std::string;
using std::stringstream;
using std::to_string;
using std::vector;

#ifdef USING_URI
	#include <sys/types.h>   /* socket, connect */
	#include <sys/socket.h>  /* socket, connect */
	#include <netinet/in.h>  /* htons           */
	#include <netdb.h>       /* gethostbyname   */
	#include <unistd.h>      /* read, write     */
	#include <string.h>      /* memcpy          */
   #include <sstream>
#endif

#include "pugiconfig.hpp"
#include "pugixml.hpp"

using pugi::xml_attribute;
using pugi::xml_document;
using pugi::xml_node;
using pugi::xpath_node;

namespace hum {

class Convert;
class HumNum;
class HumAddress;
class HumdrumToken;
typedef HumdrumToken* HTp;
class HumdrumLine;
typedef HumdrumLine* HLp;
class HumdrumFileBase;
class HumdrumFileStructure;
class HumdrumFileContent;
class HumdrumFile;
class MuseRecordBase;
class MuseRecord;
class MuseData;
class MuseDataSet;
class GridVoice;
class GotScore;


class HumParameter : public std::string {
	public:
		HumParameter(void);
		HumParameter(const std::string& str);
		HumdrumToken* origin;
};

typedef std::map<std::string, std::map<std::string, std::map<std::string, HumParameter> > > MapNNKV;
typedef std::map<std::string, std::map<std::string, HumParameter> > MapNKV;
typedef std::map<std::string, HumParameter> MapKV;

class HumHash {
	public:
		               HumHash             (void);
		              ~HumHash             ();

		std::string    getValue            (const std::string& key) const;
		std::string    getValue            (const std::string& ns2,
		                                    const std::string& key) const;
		std::string    getValue            (const std::string& ns1, const std::string& ns2,
		                                    const std::string& key) const;
		HTp            getValueHTp         (const std::string& key) const;
		HTp            getValueHTp         (const std::string& ns2,
		                                    const std::string& key) const;
		HTp            getValueHTp         (const std::string& ns1, const std::string& ns2,
		                                    const std::string& key) const;
		int            getValueInt         (const std::string& key) const;
		int            getValueInt         (const std::string& ns2,
		                                    const std::string& key) const;
		int            getValueInt         (const std::string& ns1, const std::string& ns2,
		                                    const std::string& key) const;
		HumNum         getValueFraction    (const std::string& key) const;
		HumNum         getValueFraction    (const std::string& ns2,
		                                    const std::string& key) const;
		HumNum         getValueFraction    (const std::string& ns1, const std::string& ns2,
		                                    const std::string& key)const ;
		double         getValueFloat       (const std::string& key)const ;
		double         getValueFloat       (const std::string& ns2,
		                                    const std::string& key) const;
		double         getValueFloat       (const std::string& ns1, const std::string& ns2,
		                                    const std::string& key) const;
		bool           getValueBool        (const std::string& key) const;
		bool           getValueBool        (const std::string& ns2,
		                                    const std::string& key) const;
		bool           getValueBool        (const std::string& ns1, const std::string& ns2,
		                                    const std::string& key) const;

		void           setValue            (const std::string& key,
		                                    const std::string& value);
		void           setValue            (const std::string& ns2,
		                                    const std::string& key,
		                                    const std::string& value);
		void           setValue            (const std::string& ns1,
		                                    const std::string& ns2,
		                                    const std::string& key,
		                                    const std::string& value);
		void           setValue            (const std::string& key,
		                                    const char* value);
		void           setValue            (const std::string& ns2,
		                                    const std::string& key,
		                                    const char* value);
		void           setValue            (const std::string& ns1,
		                                    const std::string& ns2,
		                                    const std::string& key,
		                                    const char* value);
		void           setValue            (const std::string& key, int value);
		void           setValue            (const std::string& ns2, const std::string& key,
		                                    int value);
		void           setValue            (const std::string& ns1, const std::string& ns2,
		                                    const std::string& key, int value);
		void           setValue            (const std::string& key, HTp value);
		void           setValue            (const std::string& ns2, const std::string& key,
		                                    HTp value);
		void           setValue            (const std::string& ns1, const std::string& ns2,
		                                    const std::string& key, HTp value);
		void           setValue            (const std::string& key, HumNum value);
		void           setValue            (const std::string& ns2, const std::string& key,
		                                    HumNum value);
		void           setValue            (const std::string& ns1, const std::string& ns2,
		                                    const std::string& key, HumNum value);
		void           setValue            (const std::string& key, double value);
		void           setValue            (const std::string& ns2, const std::string& key,
		                                    double value);
		void           setValue            (const std::string& ns1, const std::string& ns2,
		                                    const std::string& key, double value);
		bool           isDefined           (const std::string& key) const;
		bool           isDefined           (const std::string& ns2,
		                                    const std::string& key) const;
		bool           isDefined           (const std::string& ns1, const std::string& ns2,
		                                    const std::string& key) const;
		void           deleteValue         (const std::string& key);
		void           deleteValue         (const std::string& ns2, const std::string& key);
		void           deleteValue         (const std::string& ns1, const std::string& ns2,
		                                    const std::string& key);

		std::vector<std::string> getKeys   (void) const;
		std::vector<std::string> getKeys   (const std::string& ns) const;
		std::vector<std::string> getKeys   (const std::string& ns1,
		                                    const std::string& ns2) const;

		std::map<std::string, std::string> getParameters(std::string& ns1);
		std::map<std::string, std::string> getParameters(const std::string& ns1,
		                                    const std::string& ns2);

		bool           hasParameters       (void) const;
		bool           hasParameters       (const std::string& ns) const;
		bool           hasParameters       (const std::string& ns1,
		                                    const std::string& ns2) const;
		int            getParameterCount   (void) const;
		int            getParameterCount   (const std::string& ns) const;
		int            getParameterCount   (const std::string& ns1,
		                                    const std::string& ns2) const;
		void           setPrefix           (const std::string& value);
		std::string    getPrefix           (void) const;
		std::ostream&  printXml            (std::ostream& out = std::cout, int level = 0,
		                                    const std::string& indent = "\t");
		std::ostream&  printXmlAsGlobal    (std::ostream& out = std::cout, int level = 0,
		                                    const std::string& indent = "\t");

		void           setOrigin           (const std::string& key,
		                                    HumdrumToken* tok);
		void           setOrigin           (const std::string& key,
		                                    HumdrumToken& tok);
		void           setOrigin           (const std::string& ns2, const std::string& key,
		                                    HumdrumToken* tok);
		void           setOrigin           (const std::string& ns2, const std::string& key,
		                                    HumdrumToken& tok);
		void           setOrigin           (const std::string& ns1, const std::string& ns2,
		                                    const std::string& parameter,
		                                    HumdrumToken* tok);
		void           setOrigin           (const std::string& ns1, const std::string& ns2,
		                                    const std::string& parameter,
		                                    HumdrumToken& tok);

		HumdrumToken*  getOrigin           (const std::string& key) const;
		HumdrumToken*  getOrigin           (const std::string& ns2,
		                                    const std::string& key) const;
		HumdrumToken*  getOrigin           (const std::string& ns1,
		                                    const std::string& ns2,
		                                    const std::string& parameter) const;

	protected:
		void                     initializeParameters  (void);
		std::vector<std::string> getKeyList            (const std::string& keys) const;

	private:
		MapNNKV*    parameters;
		std::string prefix;

	friend std::ostream& operator<<(std::ostream& out, const HumHash& hash);
	friend std::ostream& operator<<(std::ostream& out, HumHash* hash);
};



class HumNum {
	public:
		         HumNum             (void);
		         HumNum             (int value);
		         HumNum             (int numerator, int denominator);
		         HumNum             (const HumNum& rat);
		         HumNum             (const std::string& ratstring);
		         HumNum             (const char* ratstring);
		        ~HumNum             ();

		bool     isNegative         (void) const;
		bool     isPositive         (void) const;
		bool     isZero             (void) const;
		bool     isNonZero          (void) const;
		bool     isNonNegative      (void) const;
		bool     isNonPositive      (void) const;
		bool     isInfinite         (void) const;
		bool     isFinite           (void) const;
		bool     isNaN              (void) const;
		bool     isInteger          (void) const;
		bool     isPowerOfTwo       (void) const;
		double   getFloat           (void) const;
		double   toFloat  (void) const { return getFloat(); }
		int      getInteger         (double round = 0.0) const;
		int      toInteger (double round = 0.0) const {
		                                            return getInteger(round); }
		int      getNumerator       (void) const;
		int      getDenominator     (void) const;
		HumNum   getRemainder       (void) const;
		void     setValue           (int numerator);
		void     setValue           (int numerator, int denominator);
		void     setValue           (const std::string& ratstring);
		void     setValue           (const char* ratstring);
		void     invert             (void);
		HumNum   getAbs             (void) const;
		HumNum&  makeAbs            (void);
		HumNum&  operator=          (const HumNum& value);
		HumNum&  operator=          (int value);
		HumNum&  operator+=         (const HumNum& value);
		HumNum&  operator+=         (int value);
		HumNum&  operator-=         (const HumNum& value);
		HumNum&  operator-=         (int value);
		HumNum&  operator*=         (const HumNum& value);
		HumNum&  operator*=         (int value);
		HumNum&  operator/=         (const HumNum& value);
		HumNum&  operator/=         (int value);
		HumNum   operator-          (void) const;
		HumNum   operator+          (const HumNum& value) const;
		HumNum   operator+          (int value) const;
		HumNum   operator-          (const HumNum& value) const;
		HumNum   operator-          (int value) const;
		HumNum   operator*          (const HumNum& value) const;
		HumNum   operator*          (int value) const;
		HumNum   operator/          (const HumNum& value) const;
		HumNum   operator/          (int value) const;
		bool     operator==         (const HumNum& value) const;
		bool     operator==         (double value) const;
		bool     operator==         (int value) const;
		bool     operator!=         (const HumNum& value) const;
		bool     operator!=         (double value) const;
		bool     operator!=         (int value) const;
		bool     operator<          (const HumNum& value) const;
		bool     operator<          (double value) const;
		bool     operator<          (int value) const;
		bool     operator<=         (const HumNum& value) const;
		bool     operator<=         (double value) const;
		bool     operator<=         (int value) const;
		bool     operator>          (const HumNum& value) const;
		bool     operator>          (double value) const;
		bool     operator>          (int value) const;
		bool     operator>=         (const HumNum& value) const;
		bool     operator>=         (double value) const;
		bool     operator>=         (int value) const;
		std::ostream& printFraction      (std::ostream& = std::cout) const;
		std::ostream& printMixedFraction (std::ostream& out = std::cout,
		                             std::string separator = "_") const;
		std::ostream& printList          (std::ostream& out) const;
		std::ostream& printTwoPart  (std::ostream& out, const std::string& spacer = "+") const;

	protected:
		void     reduce             (void);
		int      gcdIterative       (int a, int b);
		int      gcdRecursive       (int a, int b);

	private:
		int top;
		int bot;
};


std::ostream& operator<<(std::ostream& out, const HumNum& number);

template <typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<A>& v);



#define INVALID_INTERVAL_CLASS -123456789

// Diatonic pitch class integers:
// These could be converted into an enum provided
// that the same value are assigned to each class.
#define dpc_rest -1 /* Any negative value should be treated as a rest */
#define dpc_C 0 /* Integer for Diatonic pitch class for C */
#define dpc_D 1
#define dpc_E 2
#define dpc_F 3
#define dpc_G 4
#define dpc_A 5
#define dpc_B 6


////////////////////////////////////////////////////////////////////////////
//
// The HumPitch class is an interface for storing information about notes that will
// be used in the HumTransposer class.  The diatonic pitch class, chromatic alteration
// of the diatonic pitch and the octave are store in the class.  Names given to the
// parameters are analogous to MEI note attributes.  Note that note@accid can be also
// note/accid in MEI data, and other complications that need to be resolved into
// storing the correct pitch information in HumPitch.
//

class HumPitch {

	public:

		            HumPitch              (void)   {};
		            HumPitch              (int aDiatonic, int anAccid, int anOct);
		            HumPitch              (const HumPitch &pitch);
		            HumPitch &operator=   (const HumPitch &pitch);
		bool        isValid               (int maxAccid);
		void        setPitch              (int aDiatonic, int anAccid, int anOct);

		bool        isRest                (void) const;
		void        makeRest              (void);

		int         getOctave             (void) const;
		int         getAccid              (void) const;
		int         getDiatonicPitchClass (void) const;
		int         getDiatonicPC         (void) const;

		void        setOctave             (int anOct);
		void        setAccid              (int anAccid);
		void        makeSharp             (void);
		void        makeFlat              (void);
		void        makeNatural           (void);
		void        setDiatonicPitchClass (int aDiatonicPC);
		void        setDiatonicPC         (int aDiatonicPC);


		// conversions in/out of various representations:
		std::string getKernPitch          (void) const;
		bool        setKernPitch          (const std::string& kern);
		std::string getScientificPitch    (void) const;
		bool        setScientificPitch    (const std::string& pitch);

	protected:

		// diatonic pitch class name of pitch: C = 0, D = 1, ... B = 6.
		int m_diatonicpc;

		// chromatic alteration of pitch: 0 = natural, 1 = sharp, -2 = flat, +2 = double sharp
		int m_accid;

		// octave number of pitch: 4 = middle-C octave
		int m_oct;

		// used to convert to other formats:
		static const std::vector<char> m_diatonicPC2letterLC;
		static const std::vector<char> m_diatonicPC2letterUC;

};

std::ostream &operator<<(std::ostream &out, const HumPitch &pitch);






////////////////////////////////////////////////////////////////////////////
//
// The HumTransposer class is an interface for transposing notes represented in the
// HumPitch class format.
//

class HumTransposer {

	public:
		             HumTransposer       (void);
		            ~HumTransposer       (void);

		// Set the interval class for an octave (default is 40, +/- two sharps/flats).
		void         setMaxAccid         (int maxAccid);
		int          getMaxAccid         (void);
		void         setBase40           (void);
		void         setBase600          (void);
		int          getBase             (void);

		// Set the transposition amount for use with Transpose(void) functions.  These functions
		// need to be rerun after SetMaxAccid(void) or SetBase*(void) are called; otherwise, the
		// transposition will be 0/P1/unison.
		bool         setTransposition    (int transVal);
		bool         setTransposition    (const std::string &transString);
		bool         setTransposition    (const HumPitch &fromPitch, const std::string &toString);
		bool         setTransposition    (int keyFifths, int semitones);
		bool         setTransposition    (int keyFifths, const std::string &semitones);
		bool         setTranspositionDC  (int diatonic, int chromatic);

		// Accessor functions for retrieving stored transposition interval.
		int         getTranspositionIntervalClass  (void);
		std::string getTranspositionIntervalName   (void);

		// Transpostion based on stored transposition interval.
		void        transpose            (HumPitch &pitch);
		int         transpose            (int iPitch);

		// Transpose based on second input parameter (not with stored transposition interval).
		void        transpose            (HumPitch &pitch, int transVal);
		void        transpose            (HumPitch &pitch, const std::string &transString);

		// Convert between integer intervals and interval name strings:
		std::string getIntervalName      (const HumPitch &p1, const HumPitch &p2);
		std::string getIntervalName      (int intervalClass);
		int         getInterval          (const std::string &intervalName);

		// Convert between HumPitch class and integer pitch and interval representations.
		int humHumPitchToIntegerPitch    (const HumPitch &pitch);
		HumPitch integerPitchToHumPitch  (int ipitch);
		int         getInterval          (const HumPitch &p1, const HumPitch &p2);

		// Convert between Semitones and integer interval representation.
		std::string semitonesToIntervalName  (int keyFifths, int semitones);
		int         semitonesToIntervalClass (int keyFifths, int semitones);
		int         intervalToSemitones      (int intervalClass);
		int         intervalToSemitones      (const std::string &intervalName);

		// Circle-of-fifths related functions.
		int         intervalToCircleOfFifths      (const std::string &transString);
		int         intervalToCircleOfFifths      (int transval);
		std::string circleOfFifthsToIntervalName  (int fifths);
		int         circleOfFifthsToIntervalClass (int fifths);

		// Key-signature related functions.
		bool       getKeyTonic                     (const std::string &keyTonic,
		                                            HumPitch &tonic);
		HumPitch   circleOfFifthsToMajorTonic      (int fifths);
		HumPitch   circleOfFifthsToMinorTonic      (int fifths);
		HumPitch   circleOfFifthsToDorianTonic     (int fifths);
		HumPitch   circleOfFifthsToPhrygianTonic   (int fifths);
		HumPitch   circleOfFifthsToLydianTonic     (int fifths);
		HumPitch   circleOfFifthsToMixolydianTonic (int fifths);
		HumPitch   circleOfFifthsToLocrianTonic    (int fifths);

		// Conversions between diatonic/chromatic system and integer system of intervals.
		std::string diatonicChromaticToIntervalName(int diatonic, int chromatic);
		int  diatonicChromaticToIntervalClass (int diatonic, int chromatic);
		void intervalToDiatonicChromatic      (int &diatonic, int &chromatic, int intervalClass);
		void intervalToDiatonicChromatic      (int &diatonic, int &chromatic,
		                                       const std::string &intervalName);

		// Convenience functions for calculating common interval classes.  Augmented classes
		// can be calculated by adding 1 to perfect/major classes, and diminished classes can be
		// calcualted by subtracting 1 from perfect/minor classes.
		int    perfectUnisonClass   (void);
		int    minorSecondClass     (void);
		int    majorSecondClass     (void);
		int    minorThirdClass      (void);
		int    majorThirdClass      (void);
		int    perfectFourthClass   (void);
		int    perfectFifthClass    (void);
		int    minorSixthClass      (void);
		int    majorSixthClass      (void);
		int    minorSeventhClass    (void);
		int    majorSeventhClass    (void);
		int    perfectOctaveClass   (void);

		// Convenience functions for acessing m_diatonicMapping.
		int getCPitchClass(void) { return m_diatonicMapping[0]; }
		int getDPitchClass(void) { return m_diatonicMapping[1]; }
		int getEPitchClass(void) { return m_diatonicMapping[2]; }
		int getFPitchClass(void) { return m_diatonicMapping[3]; }
		int getGPitchClass(void) { return m_diatonicMapping[4]; }
		int getAPitchClass(void) { return m_diatonicMapping[5]; }
		int getBPitchClass(void) { return m_diatonicMapping[6]; }

		// Input string validity helper functions.
		static bool isValidIntervalName (const std::string &name);
		static bool isValidKeyTonic     (const std::string &name);
		static bool isValidSemitones    (const std::string &name);

	protected:
		// integer representation for perfect octave:
		int m_base;

		// maximum allowable sharp/flats for transposing:
		int m_maxAccid;

		// integer interval class for transposing:
		int m_transpose;

		// pitch integers for each natural diatonic pitch class:
		std::vector<int> m_diatonicMapping;

		// used to calculate semitones between diatonic pitch classes:
		static const std::vector<int> m_diatonic2semitone;

	private:
		void calculateDiatonicMapping(void);
};




class HumRegex {
	public:
		            HumRegex           (void);
		            HumRegex           (const std::string& exp,
		                                const std::string& options = "");
		           ~HumRegex           ();

		// setting persistent options for regular expression contruction
		void        setIgnoreCase      (void);
		bool        getIgnoreCase      (void);
		void        unsetIgnoreCase    (void);

		// setting persistent search/match options
		void        setGlobal          (void);
		bool        getGlobal          (void);
		void        unsetGlobal        (void);

		// replacing
		std::string&     replaceDestructive (std::string& input, const std::string& replacement,
		                                const std::string& exp);
		std::string&     replaceDestructive (std::string& input, const std::string& replacement,
		                                const std::string& exp,
		                                const std::string& options);
		std::string      replaceCopy        (const std::string& input,
		                                const std::string& replacement,
		                                const std::string& exp);
		std::string      replaceCopy        (const std::string& input,
		                                const std::string& replacement,
		                                const std::string& exp,
		                                const std::string& options);

		std::string&     replaceDestructive (std::string* input, const std::string& replacement,
		                                const std::string& exp);
		std::string&     replaceDestructive (std::string* input, const std::string& replacement,
		                                const std::string& exp,
		                                const std::string& options);
		std::string      replaceCopy        (std::string* input, const std::string& replacement,
		                                const std::string& exp);
		std::string      replaceCopy        (std::string* input, const std::string& replacement,
		                                const std::string& exp,
		                                const std::string& options);
		std::string       makeSafeCopy  (const std::string& input);
		std::string&      makeSafeDestructive(std::string& inout);
		std::string&      tr            (std::string& input, const std::string& from,
		                                const std::string& to);

		// matching (full-string match)
		bool        match              (const std::string& input, const std::string& exp);
		bool        match              (const std::string& input, const std::string& exp,
		                                const std::string& options);
		bool        match              (const std::string* input, const std::string& exp);
		bool        match              (const std::string* input, const std::string& exp,
		                                const std::string& options);


		// searching
		// http://www.cplusplus.com/reference/regex/regex_search
		int         search             (const std::string& input, const std::string& exp);
		int         search             (const std::string& input, const std::string& exp,
		                                const std::string& options);
		int         search             (const std::string& input, int startindex,
		                                const std::string& exp);
		int         search             (const std::string& input, int startindex,
		                                const std::string& exp,
		                                const std::string& options);

		int         search             (std::string* input, const std::string& exp);
		int         search             (std::string* input, const std::string& exp,
		                                const std::string& options);
		int         search             (std::string* input, int startindex,
		                                const std::string& exp);
		int         search             (std::string* input, int startindex,
		                                const std::string& exp,
		                                const std::string& options);

		int         getMatchCount      (void);
		std::string getMatch           (int index);
		int         getMatchInt        (int index);
		double      getMatchDouble     (int index);
		std::string getPrefix          (void);
		std::string getSuffix          (void);
		int         getMatchStartIndex (int index = 0);
		int         getMatchEndIndex   (int index = 0);
		int         getMatchLength     (int index = 0);

		// token lists:
		bool        split              (std::vector<std::string>& entries,
		                                const std::string& buffer,
		                                const std::string& separator);

	protected:
		std::regex_constants::syntax_option_type
				getTemporaryRegexFlags(const std::string& sflags);
		std::regex_constants::match_flag_type
				getTemporarySearchFlags(const std::string& sflags);


	private:

		// m_regex: stores the regular expression to use as a default.
		//
		// http://en.cppreference.com/w/cpp/regex/basic_regex
		// .assign(string) == set the regular expression.
		// operator=       == set the regular expression.
		// .flags()        == return syntax_option_type used to construct.
		std::regex m_regex;

		// m_matches: stores the matches from a search:
		//
		// http://en.cppreference.com/w/cpp/regex/match_results
		// .empty()     == check if match was successful.
		// .size()      == number of matches.
		// .length(i)   == return length of a submatch.
		// .position(i) == return start index of submatch in search string.
		// .str(i)      == return string of submatch.
		// operator[i]  == return submatch.
		// .prefix
		// .suffix
		// .begin()     == start of submatch list.
		// .end()       == end of submatch list.
		std::smatch m_matches;

		// m_regexflags: store default settings for regex processing
		// http://en.cppreference.com/w/cpp/regex/syntax_option_type
		// http://en.cppreference.com/w/cpp/regex/basic_regex
		// /usr/local/Cellar/gcc49/4.9.3/include/c++/4.9.3/bits/regex_constants.h
		//
		// Options (in the namespace std::regex_constants):
		//    icase      == Ignore case.
		//    nosubs     == Don't collect submatches.
		//    optimize   == Make matching faster, but construction slower.
		//    collate    == locale character ranges.
		//    multiline  == C++17 only.
		//
		// Only one of the following can be given.  EMCAScript will be
		// used by default if none specified.
		//    EMCAScript == Use EMCAScript regex syntax.
		//    basic      == Use basic POSIX syntax.
		//    extended   == Use extended POSIX syntax.
		//    awk        == Use awk POSIX syntax.
		//    grep       == Use grep POSIX syntax.
		//    egrep      == Use egrep POSIX syntax.
		std::regex_constants::syntax_option_type m_regexflags;

		// m_flags: store default settings for regex processing
		// http://www.cplusplus.com/reference/regex/regex_search
		//    match_default     == clear all options.
		//    match_not_bol     == not beginning of line.
		//    match_not_eol     == not end of line.
		//    match_not_bow     == not beginning of word for \b.
		//    match_not_eow     == not end of word for \b.
		//    match_any         == any match acceptable if more than 1 possible..
		//    match_not_null    == empty sequence does note match.
		//    match_continuous  ==
		//    match_prev_avail  ==
		//    format_default    == same as match_default.
		std::regex_constants::match_flag_type m_searchflags;

};



enum signifier_type {
	signifier_unknown,
	signifier_link,
	signifier_above,
	signifier_below
};

class HumSignifier {

	public:
		            HumSignifier     (void);
		            HumSignifier     (const std::string& rdfline);
		           ~HumSignifier     ();
		bool        parseSignifier   (const std::string& rdfline);
		void        clear            (void);
		std::string getSignifier     (void);
		std::string getDefinition    (void);
		std::string getParameter     (const std::string& key);
		bool        isKernLink       (void);
		bool        isKernAbove      (void);
		bool        isKernBelow      (void);

	private:
		std::string m_exinterp;
		std::string m_signifier;
		std::string m_definition;
		int         m_sigtype = signifier_type::signifier_unknown;
		std::map<std::string, std::string> m_parameters;
};



class HumSignifiers {
	public:
		              HumSignifiers    (void);
		             ~HumSignifiers    ();

		void          clear            (void);
		bool          addSignifier     (const std::string& rdfline);
		bool          hasKernLinkSignifier (void);
		std::string   getKernLinkSignifier (void);
		bool          hasKernAboveSignifier (void);
		std::string   getKernAboveSignifier (void);
		bool          hasKernBelowSignifier (void);
		std::string   getKernBelowSignifier (void);
		int           getSignifierCount(void);
		HumSignifier* getSignifier(int index);

	private:
		std::vector<HumSignifier*> m_signifiers;
		int  m_kernLinkIndex = -1;
		int  m_kernAboveIndex = -1;
		int  m_kernBelowIndex = -1;

};



class HumdrumLine;
typedef HumdrumLine* HLp;

class HumdrumToken;
typedef HumdrumToken* HTp;

class HumAddress {
	public:
		                    HumAddress        (void);
		                    HumAddress        (HumAddress& address);
		                   ~HumAddress        ();

		HumAddress&         operator=         (const HumAddress& address);
		int                 getLineIndex      (void) const;
		int                 getLineNumber     (void) const;
		int                 getFieldIndex     (void) const;
		const HumdrumToken& getDataType       (void) const;
		HTp                 getExclusiveInterpretation(void);
		const std::string&  getSpineInfo      (void) const;
		int                 getTrack          (void) const;
		int                 getSubtrack       (void) const;
		int                 getSubtrackCount  (void) const;
		std::string         getTrackString    (std::string separator = ".") const;
		HLp                 getLine           (void) const;
		HLp                 getOwner          (void) const { return getLine(); }
		bool                hasOwner          (void) const;

	protected:
		void                setOwner          (HLp aLine);
		void                setFieldIndex     (int fieldlindex);
		void                setSpineInfo      (const std::string& spineinfo);
		void                setTrack          (int aTrack, int aSubtrack);
		void                setTrack          (int aTrack);
		void                setSubtrack       (int aSubtrack);
		void                setSubtrackCount  (int aSubtrack);

	private:

		// fieldindex: This is the index of the token in the HumdrumLine
		// which owns this token.
		int m_fieldindex;

		// spining: This is the spine position of the token. A simple spine
		// position is an integer, starting with "1" for the first spine
		// of the file (left-most spine).  When the spine splits, "(#)a"
		// is wrapped around the left-subspine's spine info, and "(#)b"
		// around the right-subspine's info. Merged spines will add a space
		// between the two or more merged spines information, such as
		// "(#)a (#)b" for two sub-spines merged into a single spine again.
		// But in this case there is a spine info simplification which will
		// convert "(#)a (#)b" into "#" where # is the original spine number.
		// Other more complicated mergers may be simplified in the future.
		std::string m_spining;

		// track: This is the track number of the spine.  It is the first
		// number found in the spineinfo string.
		int m_track;

		// subtrack: This is the subtrack number for the spine.  When a spine
		// is not split, it will be 0, if the spine has been split with *^,
		// then the left-subspine will be in subtrack 1 and the right-spine
		// will be subtrack 2.  If subspines are exchanged with *x, then their
		// subtrack assignments will also change.
		int m_subtrack;

		// subtrackcount: The number of currently active subtracks tokens
		// on the owning HumdrumLine (in the same track).  The subtrack range
		// is from 1 (if there is only a primary spine), to a larger number.
		// if subtrackcount is 0, then the variable is not set, or there are
		// no tokens in the track (such as for global comments).
		int m_subtrackcount;

		// owner: This is the line which manages the given token.
		HLp          m_owner;

	friend class HumdrumToken;
	friend class HumdrumLine;
	friend class HumdrumFile;
};



class HumParamSet {

	public:
		              HumParamSet        (void);
		              HumParamSet        (const std::string& token);
		              HumParamSet        (HTp token);
		             ~HumParamSet        ();

		const std::string& getNamespace1 (void);
		const std::string& getNamespace2 (void);
		std::string   getNamespace       (void);
		void          setNamespace1      (const std::string& name);
		void          setNamespace2      (const std::string& name);
		void          setNamespace       (const std::string& name);
		void          setNamespace       (const std::string& name1, const std::string& name2);
		HTp           getToken           (void) { return m_token; }

		void          clear              (void);
		int           getCount           (void);
		const std::string& getParameterName   (int index);
		const std::string& getParameterValue  (int index);
		int           addParameter       (const std::string& name, const std::string& value);
		int           setParameter       (const std::string& name, const std::string& value);
		void          readString         (const std::string& text);
		void          readString         (HTp token);
		std::ostream& printXml           (std::ostream& out = std::cout, int level = 0,
		                                  const std::string& indent = "\t");

	private:
		HTp         m_token = NULL;
		std::string m_ns1;
		std::string m_ns2;
		std::vector<std::pair<std::string, std::string>> m_parameters;

};


std::ostream& operator<<(std::ostream& out, HumParamSet* hps);
std::ostream& operator<<(std::ostream& out, HumParamSet& hps);



class _HumInstrument {
	public:
		_HumInstrument    (void) { humdrum = ""; name = ""; gm = 0; }
	  ~_HumInstrument    ()     { humdrum = ""; name = ""; gm = 0; }

		std::string humdrum;
		std::string name;
		int         gm;
};


class HumInstrument {
	public:
		            HumInstrument       (void);
		            HumInstrument       (const std::string& Hname);
		           ~HumInstrument       ();

		std::string getName             (void);
		std::string getName             (const std::string& Hname);
		std::string getHumdrum          (void);
		int         getGM               (void);
		int         getGM               (const std::string& Hname);
		void        setHumdrum          (const std::string& Hname);
		int         setGM               (const std::string& Hname, int aValue);

	private:
		int                            m_index;
		static std::vector<_HumInstrument>  m_data;
		static int                     m_classcount;

	protected:
		void       initialize          (void);
		void       afi                 (const char* humdrum_name, int midinum,
		                                const char* EN_name);
		int        find                (const std::string& Hname);
		void       sortData            (void);
		static int data_compare_by_humdrum_name(const void* a, const void* b);
};


///////////////////////////////////////////////////////////////////////////
//
// General MIDI instrument definitions
//

#define  CH_1                             0
#define  CH_2                             1
#define  CH_3                             2
#define  CH_4                             3
#define  CH_5                             4
#define  CH_6                             5
#define  CH_7                             6
#define  CH_8                             7
#define  CH_9                             8
#define  CH_10                            9
#define  CH_11                            10
#define  CH_12                            11
#define  CH_13                            12
#define  CH_14                            13
#define  CH_15                            14
#define  CH_16                            15

#define  GM_PIANO(X)                      (0+(X))
#define  GM_ACOUSTIC_GRAND_PIANO          (0)
#define  GM_BRIGHT_ACOUSTIC_PIANO         (1)
#define  GM_ELECTRIC_GRAND_PIANO          (1)
#define  GM_HONKYTONK_PIANO               (2)
#define  GM_HONKY_TONK_PIANO              (3)
#define  GM_ELECTRIC_PIANO_1              (4)
#define  GM_ELECTRIC_PIANO_2              (5)
#define  GM_HARPSICHORD                   (6)
#define  GM_CLAVI                         (7)

#define  GM_CHROMATIC(X)                  (8+(X))
#define  GM_CELESTA                       (8)
#define  GM_GLOCKENSPIEL                  (9)
#define  GM_MUSIC_BOX                     (10)
#define  GM_VIBRAPHONE                    (11)
#define  GM_MARIMBA                       (12)
#define  GM_XYLOPHONE                     (13)
#define  GM_TUBULAR_BELLS                 (14)
#define  GM_DULCIMER                      (15)

#define  GM_ORGAN(X)                      (16+(X))
#define  GM_DRAWBAR_ORGAN                 (16)
#define  GM_PERCUSSIVE_ORGAN              (17)
#define  GM_ROCK_ORGAN                    (18)
#define  GM_CHURCH_ORGAN                  (19)
#define  GM_REED_ORGAN                    (20)
#define  GM_ACCORDION                     (21)
#define  GM_HARMONICA                     (22)
#define  GM_TANGO_ACCORDION               (23)

#define  GM_GUITAR(X)                     (24+(X))
#define  GM_ACOUSTIC_GUITAR_NYLON         (24)
#define  GM_ACOUSTIC_GUITAR_STEEL         (25)
#define  GM_ELECTRIC_GUITAR_JAZZ          (26)
#define  GM_ELECTRIC_GUITAR_CLEAN         (27)
#define  GM_ELECTRIC_GUITAR_MUTED         (28)
#define  GM_OVERDRIVEN_GUITAR             (29)
#define  GM_DISTORTION_GUITAR             (30)
#define  GM_GUITAR_HARMONICS              (31)

#define  GM_BASS(X)                       (32+(X))
#define  GM_ACOUSTIC_BASS                 (32)
#define  GM_ELECTRIC_BASS_FINGER          (33)
#define  GM_ELECTRIC_BASS_PICK            (34)
#define  GM_FRETLESS_BASS                 (35)
#define  GM_SLAP_BASS_1                   (36)
#define  GM_SLAP_BASS_2                   (37)
#define  GM_SYNTH_BASS_1                  (38)
#define  GM_SYNTH_BASS_2                  (39)

#define  GM_STRINGS(X)                    (40+(X))
#define  GM_VIOLIN                        (40)
#define  GM_VIOLA                         (41)
#define  GM_CELLO                         (42)
#define  GM_CONTRABASS                    (43)
#define  GM_TREMOLO_STRINGS               (44)
#define  GM_PIZZACATO_STRINGS             (45)
#define  GM_ORCHESTRAL_HARP               (46)
#define  GM_TIMPANI                       (47)

#define  GM_ENSEMBLE(X)                   (48+(X))
#define  GM_STRING_ENSEMBLE_1             (48)
#define  GM_STRING_ENSEMBLE_2             (49)
#define  GM_SYNTHSTRINGS_1                (50)
#define  GM_SYNTHSTRINGS_2                (51)
#define  GM_CHOIR_AAHS                    (52)
#define  GM_VOICE_OOHS                    (53)
#define  GM_SYNTH_VOICE                   (54)
#define  GM_ORCHESTRA_HIT                 (55)

#define  GM_BRASS(X)                      (56+(X))
#define  GM_TRUMPET                       (56)
#define  GM_TROMBONE                      (57)
#define  GM_TUBA                          (58)
#define  GM_MUTED_TRUMPED                 (59)
#define  GM_FRENCH_HORN                   (60)
#define  GM_BRASS_SECTION                 (61)
#define  GM_SYNTHBRASS_1                  (62)
#define  GM_SYNTHBRASS_2                  (63)

#define  GM_REED(X)                       (64+(X))
#define  GM_SOPRANO_SAX                   (64)
#define  GM_ALTO_SAX                      (65)
#define  GM_TENOR_SAX                     (66)
#define  GM_BARITONE_SAX                  (67)
#define  GM_OBOE                          (68)
#define  GM_ENGLISH_HORN                  (69)
#define  GM_BASSOON                       (70)
#define  GM_CLARINET                      (71)

#define  GM_PIPE(X)                       (72+(X))
#define  GM_PICCOLO                       (72)
#define  GM_FLUTE                         (73)
#define  GM_RECORDER                      (74)
#define  GM_PAN_FLUTE                     (75)
#define  GM_BLOWN_BOTTLE                  (76)
#define  GM_SHAKUHACHI                    (77)
#define  GM_WHISTLE                       (78)
#define  GM_OCARINA                       (79)

#define  GM_LEAD(X)                       (80+(X))
#define  GM_LEAD_SQUARE                   (80)
#define  GM_LEAD_SAWTOOTH                 (81)
#define  GM_LEAD_CALLIOPE                 (82)
#define  GM_LEAD_CHIFF                    (83)
#define  GM_LEAD_CHARANG                  (84)
#define  GM_LEAD_VOICE                    (85)
#define  GM_LEAD_FIFTHS                   (86)
#define  GM_LEAD_BASS                     (87)

#define  GM_PAD(X)                        (88+(X))
#define  GM_PAD_NEW_AGE                   (88)
#define  GM_PAD_WARM                      (89)
#define  GM_PAD_POLYSYNTH                 (90)
#define  GM_PAD_CHOIR                     (91)
#define  GM_PAD_BOWED                     (92)
#define  GM_PAD_METALLIC                  (93)
#define  GM_PAD_HALO                      (94)
#define  GM_PAD_SWEEP                     (95)

#define  GM_FX(X)                         (96+(X))
#define  GM_FX_TRAIN                      (96)
#define  GM_FX_SOUNDTRACK                 (97)
#define  GM_FX_CRYSTAL                    (98)
#define  GM_FX_ATMOSPHERE                 (99)
#define  GM_FX_BRIGHTNESS                 (100)
#define  GM_FX_GOBLINS                    (101)
#define  GM_FX_ECHOES                     (102)
#define  GM_FX_SCI_FI                     (103)

#define  GM_ETHNIC(X)                     (104+(X))
#define  GM_SITAR                         (104)
#define  GM_BANJO                         (105)
#define  GM_SHAMISEN                      (106)
#define  GM_KOTO                          (107)
#define  GM_KALIMBA                       (108)
#define  GM_BAGPIPE                       (109)
#define  GM_FIDDLE                        (110)
#define  GM_SHANAI                        (111)

#define  GM_PERCUSSION(X)                 (112+(X))
#define  GM_TINKLE_BELL                   (112)
#define  GM_AGOGO                         (113)
#define  GM_STEEL_DRUMS                   (114)
#define  GM_WOODBLOCKS                    (115)
#define  GM_TAIKO_DRUM                    (116)
#define  GM_MELODIC_DRUM                  (117)
#define  GM_SYNTH_DRUM                    (118)
#define  GM_REVERSE_CYMBAL                (119)

#define  GM_SOUNDEFFECT(X)                (120+(X))
#define  GM_GUITAR_FRET_NOISE             (120)
#define  GM_BREATH_NOISE                  (121)
#define  GM_SEASHORE                      (122)
#define  GM_BIRD_TWEET                    (123)
#define  GM_TELEPHONE_RING                (124)
#define  GM_HELICOPTER                    (125)
#define  GM_APPLAUSE                      (126)
#define  GM_GUNSHOT                       (127)

//
// Percussion instruments on channel 10
//

#define  GM_ACOUSTIC_BASS_DRUM            (35)
#define  GM_BASS_DRUM_1                   (36)
#define  GM_SIDE_STICK                    (37)
#define  GM_ACOUSTIC_SNARE                (38)
#define  GM_HAND_CLAP                     (39)
#define  GM_ELECTRIC_SNARE                (40)
#define  GM_LOW_FLOOR_TOM                 (41)
#define  GM_CLOSED_HI_HAT                 (42)
#define  GM_HIGH_FLOOR_TOM                (43)
#define  GM_PEDAL_HI_HAT                  (44)
#define  GM_LOW_TOM                       (45)
#define  GM_OPEN_HI_HAT                   (46)
#define  GM_LOW_MID_TOM                   (47)
#define  GM_HIGH_MID_TOM                  (48)
#define  GM_CRASH_CYMBAL_1                (49)
#define  GM_HIGH_TOM                      (50)
#define  GM_RIDE_CYMBAL_1                 (51)
#define  GM_CHINESE_CYMBAL                (52)
#define  GM_RIDE_BELL                     (53)
#define  GM_TAMBOURINE                    (54)
#define  GM_SPLASH_CYMBAL                 (55)
#define  GM_COWBELL                       (56)
#define  GM_CRASH_CYMBAL_2                (57)
#define  GM_VIBRASLAP                     (58)
#define  GM_RIDE_CYMBAL_2                 (59)
#define  GM_HI_BONGO                      (60)
#define  GM_LOW_BONGO                     (61)
#define  GM_MUTE_HI_CONGA                 (62)
#define  GM_OPEN_HI_CONGA                 (63)
#define  GM_LOW_CONGA                     (64)
#define  GM_HIGH_TIMBALE                  (65)
#define  GM_LOW_TIMBALE                   (66)
#define  GM_HIGH_AGOGO                    (67)
#define  GM_LOW_AGOGO                     (68)
#define  GM_CABASA                        (69)
#define  GM_MARACAS                       (70)
#define  GM_SHORT_WHISTLE                 (71)
#define  GM_LONG_WHISTLE                  (72)
#define  GM_SHORT_GUIRO                   (73)
#define  GM_LONG_GUIRO                    (74)
#define  GM_CLAVES                        (75)
#define  GM_HI_WOOD_BLOCK                 (76)
#define  GM_LOW_WOOD_BLOCK                (77)
#define  GM_MUTE_CUICA                    (78)
#define  GM_OPEN_CUICA                    (79)
#define  GM_MUTE_TRIANGLE                 (80)
#define  GM_OPEN_TRIANGLE                 (81)



typedef HumdrumLine* HLp;

class HumdrumLine : public std::string, public HumHash {
	public:
		            HumdrumLine            (void);
		            HumdrumLine            (const std::string& aString);
		            HumdrumLine            (const char* aString);
		            HumdrumLine            (HumdrumLine& line);
		            HumdrumLine            (HumdrumLine& line, void* owner);
		           ~HumdrumLine            ();

		HumdrumLine& operator=             (HumdrumLine& line);
		bool        isComment              (void) const;
		bool        isCommentLocal         (void) const;
		bool        isLocalComment         (void) const { return isCommentLocal(); }
		bool        isCommentGlobal        (void) const;
		bool        isCommentUniversal     (void) const;
		bool        isReference            (void) const;
		bool        isReferenceRecord      (void) const { return isReference(); }
		bool        isGlobalReference      (void) const;
		bool        isUniversalReference   (void) const;
		bool        isSignifier            (void) const;
		std::string getReferenceKey        (void) const;
		std::string getReferenceValue      (void) const;
		std::string getGlobalReferenceKey      (void) const;
		std::string getGlobalReferenceValue    (void) const;
		std::string getUniversalReferenceKey   (void) const;
		std::string getUniversalReferenceValue (void) const;
		bool        isUniversalComment     (void) const { return isCommentUniversal(); }
		bool        isGlobalComment        (void) const { return isCommentGlobal(); }
		bool        isExclusive            (void) const;
		bool        isExclusiveInterpretation (void) const { return isExclusive(); }
		bool        isTerminator           (void) const;
		bool        isInterp               (void) const;
		bool        isInterpretation       (void) const { return isInterp(); }
		bool        isBarline              (void) const;
		bool        isData                 (void) const;
		bool        isGraceLine            (void);
		bool        isAllNull              (void) const;
		bool        isAllRhythmicNull      (void) const;
		bool        isEmpty                (void) const;
		bool        isBlank                (void) const { return isEmpty(); }
		bool        isManipulator          (void) const;
		bool        hasSpines              (void) const;
		bool        isGlobal               (void) const;

		int         isKeySignature         (int startTrack = 0, int stopTrack = 0);
		int         isKeyDesignation       (int startTrack = 0, int stopTrack = 0);
		int         isTempo                (int startTrack = 0, int stopTrack = 0);
		int         isTimeSignature        (int startTrack = 0, int stopTrack = 0);
		int         isExpansionLabel       (int startTrack = 0, int stopTrack = 0);
		int         isExpansionList        (int startTrack = 0, int stopTrack = 0);

		bool        equalFieldsQ           (const std::string& exinterp, const std::string& value);
		HTp         token                  (int index) const;
		void        getTokens              (std::vector<HTp>& list);
		int         getTokenCount          (void) const;
		int         getFieldCount          (void) const { return getTokenCount(); }
		std::string getTokenString         (int index) const;
		bool        equalChar              (int index, char ch) const;
		char        getChar                (int index) const;
		bool        isKernBoundaryStart    (void) const;
		bool        isKernBoundaryEnd      (void) const;
		std::ostream& printSpineInfo       (std::ostream& out = std::cout);
		std::ostream& printTrackInfo       (std::ostream& out = std::cout);
		std::ostream& printDataTypeInfo    (std::ostream& out = std::cout);
		std::ostream& printDurationInfo    (std::ostream& out = std::cout);
		std::ostream& printCsv             (std::ostream& out = std::cout,
		                                    const std::string& separator = ",");
		std::ostream& printXml             (std::ostream& out = std::cout, int level = 0,
		                                    const std::string& indent = "\t");
		std::ostream& printXmlParameterInfo(std::ostream& out, int level,
		                                    const std::string& indent);
		std::ostream& printGlobalXmlParameterInfo(std::ostream& out, int level,
		                                    const std::string& indent);
		std::string   getXmlId             (const std::string& prefix = "") const;
		std::string   getXmlIdPrefix       (void) const;
		void          clearTokenLinkInfo   (void);
		void          createLineFromTokens (void);
		void          generateLineFromTokens (void) { createLineFromTokens(); }
		void          removeExtraTabs      (void);
		void          addExtraTabs         (std::vector<int>& trackWidths);
		int           getLineIndex         (void) const;
		int           getLineNumber        (void) const;
		HumdrumFile*  getOwner             (void);
		void          setText              (const std::string& text);
		std::string   getText              (void);
		int           getBarNumber         (void);
		int           getMeasureNumber     (void) { return getBarNumber(); }

		HumNum      getDuration            (void);
		HumNum      getDurationFromStart   (void);
		HumNum      getDurationToEnd       (void);
		HumNum      getDurationFromBarline (void);
		HumNum      getDurationToBarline   (void);
		HumNum      getBarlineDuration     (void);

		HumNum      getDuration            (HumNum scale);
		HumNum      getDurationFromStart   (HumNum scale);
		HumNum      getDurationToEnd       (HumNum scale);
		HumNum      getDurationFromBarline (HumNum scale);
		HumNum      getDurationToBarline   (HumNum scale);
		HumNum      getBarlineDuration     (HumNum scale);
		int         getKernNoteAttacks     (void);
		int         addLinkedParameter     (HTp token);

		HumNum   getBeat                (HumNum beatdur = 1);
		HumNum   getBeatStr             (std::string beatrecip = "4");
		HTp      getTrackStart          (int track) const;
		HTp      getTrackEnd            (int track, int subtrack = 0) const;
		void     setLineFromCsv         (const char* csv,
		                                 const std::string& separator = ",");
		void     setLineFromCsv         (const std::string& csv,
		                                 const std::string& separator = ",");

		// pitch-related functions, defined in HumdrumLine-kern.cpp:

		void             getMidiPitches       (std::vector<int>& output);
		std::vector<int> getMidiPitches       (void);
		void             getMidiPitchesSortHL (std::vector<int>& output);
		std::vector<int> getMidiPitchesSortHL (void);
		void             getMidiPitchesSortLH (std::vector<int>& output);
		std::vector<int> getMidiPitchesSortLH (void);

		void             getMidiPitchesResolveNull       (std::vector<int>& output);
		std::vector<int> getMidiPitchesResolveNull       (void);
		void             getMidiPitchesResolveNullSortHL (std::vector<int>& output);
		std::vector<int> getMidiPitchesResolveNullSortHL (void);
		void             getMidiPitchesResolveNullSortLH (std::vector<int>& output);
		std::vector<int> getMidiPitchesResolveNullSortLH (void);


		// low-level editing functions (need to re-analyze structure after using)
		void     appendToken            (HTp token, int tabcount = 1);
		void     appendToken            (const HumdrumToken& token, int tabcount = 1);
		void     appendToken            (const std::string& token, int tabcount = 1);
		void     appendToken            (const char* token, int tabcount = 1);

		void     appendToken            (int index, HTp token, int tabcount = 1);
		void     appendToken            (int index, const HumdrumToken& token, int tabcount = 1);
		void     appendToken            (int index, const std::string& token, int tabcount = 1);
		void     appendToken            (int index, const char* token, int tabcount = 1);

		void     insertToken            (int index, HTp token, int tabcount = 1);
		void     insertToken            (int index, const HumdrumToken& token, int tabcount = 1);
		void     insertToken            (int index, const std::string& token, int tabcount = 1);
		void     insertToken            (int index, const char* token, int tabcount = 1);

		void     setDuration            (HumNum aDur);
		void     setDurationFromStart   (HumNum dur);
		void     setDurationFromBarline (HumNum dur);
		void     setDurationToBarline   (HumNum dur);

		void     copyStructure          (HLp line, const std::string& empty);

		bool     allSameBarlineStyle    (void);
		bool     hasDataStraddle        (void);

	protected:
		bool     analyzeTracks          (std::string& err);
		bool     analyzeTokenDurations  (std::string& err);
		void     setLineIndex           (int index);
		void     clear                  (void);
		void     setOwner               (void* hfile);
		int      createTokensFromLine   (void);
		void     setLayoutParameters    (void);
		void     setParameters          (const std::string& pdata);
		void     storeGlobalLinkedParameters(void);
		std::ostream&	printXmlGlobalLinkedParameterInfo(std::ostream& out = std::cout, int level = 0,
		                                 const std::string& indent = "\t");
		std::ostream& printXmlGlobalLinkedParameters(std::ostream& out = std::cout, int level = 0,
		                                 const std::string& indent = "\t");

	private:

		//
		// State variables managed by the HumdrumLine class:
		//

		// m_lineindex: Used to store the index number of the HumdrumLine in
		// the owning HumdrumFile object.
		// This variable is filled by HumdrumFileStructure::analyzeLines().
		int m_lineindex;

		// m_tokens: Used to store the individual tab-separated token fields
		// on a line.  These are prepared automatically after reading in
		// a full line of text (which is accessed throught the string parent
		// class).  If the full line is changed, the tokens are not updated
		// automatically -- use createTokensFromLine().  Likewise the full
		// text line is not updated if any tokens are changed -- use
		// createLineFromTokens() in that case.  The second case is more
		// useful: you can read in a HumdrumFile, tweak the tokens, then
		// reconstruct the full line and print out again.
		// This variable is filled by HumdrumFile::read().
		// The contents of this vector should be deleted when deconstructing
		// a HumdrumLine object.
		std::vector<HumdrumToken*> m_tokens;

		// m_tabs: Used to store a count of the number of tabs between
		// each token on a line.  This is the number of tabs after the
		// token at the given index (so no tabs before the first token).
		std::vector<int> m_tabs;

		// m_duration: This is the "duration" of a line.  The duration is
		// equal to the minimum time unit of all durational tokens on the
		// line.  This also includes null tokens when the duration of a
		// previous note in a previous spine is ending on the line, so it is
		// not just the minimum duration on the line.
		// This variable is filled by HumdrumFileStructure::analyzeRhythm().
		HumNum m_duration;

		// m_durationFromStart: This is the cumulative duration of all lines
		// prior to this one in the owning HumdrumFile object.  For example,
		// the first notes in a score start at time 0, If the duration of the
		// first data line is 1 quarter note, then the durationFromStart for
		// the second line will be 1 quarter note.
		// This variable is filled by HumdrumFileStructure::analyzeRhythm().
		HumNum m_durationFromStart;

		// m_durationFromBarline: This is the cumulative duration from the
		// last barline to the current data line.
		// This variable is filled by HumdrumFileStructure::analyzeMeter().
		HumNum m_durationFromBarline;

		// m_durationToBarline: This is the duration from the start of the
		// current line to the next barline in the owning HumdrumFile object.
		// This variable is filled by HumdrumFileStructure::analyzeMeter().
		HumNum m_durationToBarline;

		// m_linkedParameters: List of Humdrum tokens which are parameters
		// (mostly only layout parameters at the moment)
		std::vector<HTp> m_linkedParameters;

		// m_rhythm_analyzed: True if duration information from HumdrumFile
		// has been added to line.
		bool m_rhythm_analyzed = false;

		// owner: This is the HumdrumFile which manages the given line.
		void* m_owner;

	friend class HumdrumFileBase;
	friend class HumdrumFileStructure;
	friend class HumdrumFileContent;
	friend class HumdrumFile;
};

std::ostream& operator<< (std::ostream& out, HumdrumLine& line);
std::ostream& operator<< (std::ostream& out, HLp line);




typedef HumdrumToken* HTp;

class HumdrumToken : public std::string, public HumHash {
	public:
		         HumdrumToken              (void);
		         HumdrumToken              (const HumdrumToken& token);
		         HumdrumToken              (HumdrumToken* token);
		         HumdrumToken              (const HumdrumToken& token, HLp owner);
		         HumdrumToken              (HumdrumToken* token, HLp owner);
		         HumdrumToken              (const char* token);
		         HumdrumToken              (const std::string& token);
		        ~HumdrumToken              ();

		bool     isNull                    (void) const;
		bool     isNullToken               (void) const { return isNull(); }
		bool     isManipulator             (void) const;
		bool     isSpineManipulator        (void) const { return isManipulator(); }

		bool     isExclusiveInterpretation (void) const;
		bool     isSplitInterpretation     (void) const;
		bool     isMergeInterpretation     (void) const;
		bool     isExchangeInterpretation  (void) const;
		bool     isTerminateInterpretation (void) const;
		bool     isAddInterpretation       (void) const;

		// alises for the above
		bool     isExclusive               (void) const
		                                  { return isExclusiveInterpretation(); }
		bool     isExInterp                (void) const
		                                  { return isExclusiveInterpretation(); }
		bool     isSplit                   (void) const
		                                      { return isSplitInterpretation(); }
		bool     isMerge                   (void) const
		                                      { return isMergeInterpretation(); }
		bool     isExchange                (void) const
		                                   { return isExchangeInterpretation(); }
		bool     isTerminate               (void) const
		                                  { return isTerminateInterpretation(); }
		bool     isTerminator              (void) const
		                                  { return isTerminateInterpretation(); }
		bool     isAdd                     (void) const
		                                      { return isSplitInterpretation(); }

		bool     isBarline                 (void) const;
		bool     isCommentLocal            (void) const;
		bool     isLocalComment            (void) const { return isCommentLocal(); }
		bool     isCommentGlobal           (void) const;
		bool     isGlobalComment           (void) const { return isCommentGlobal(); }
		bool     isComment                 (void) const;
		bool     isData                    (void) const;
		bool     isInterpretation          (void) const;
		bool     isNonNullData             (void) const;
		bool     isNullData                (void) const;
		bool     isChord                   (const std::string& separator = " ");
		bool     isLabel                   (void) const;
		bool     isExpansionLabel          (void) const { return isLabel(); };
		bool     isExpansionList           (void) const;
		bool     hasRhythm                 (void) const;
		bool     hasBeam                   (void) const;
		bool     hasFermata                (void) const;
		bool     equalTo                   (const std::string& pattern);
		bool     isStaff                   (void) const;

		// kern-specific functions:
		bool     isRest                    (void);
		bool     isNote                    (void);
		bool     isUnpitched               (void);
		bool     isPitched                 (void);
		bool     isSecondaryTiedNote       (void);
		bool     isSustainedNote           (void);
		bool     isNoteSustain             (void) { return isSustainedNote(); }
		bool     isNoteAttack              (void);
		bool     isInvisible               (void);
		bool     isGrace                   (void);
		bool     isClef                    (void);
		bool     isModernClef              (void);
		bool     isOriginalClef            (void);
		bool     isKeySignature            (void);
		bool     isModernKeySignature      (void);
		bool     isOriginalKeySignature    (void);
		bool     isKeyDesignation          (void);
		bool     isTimeSignature           (void);
		bool     isMetricSymbol            (void);
		bool     isMeterSymbol             (void) { return isMetricSymbol(); }
		bool     isMeterSignature          (void) { return isMetricSymbol(); }
		bool     isMetricSignature         (void) { return isMetricSymbol(); }
		bool     isTempo                   (void);
		bool     isMensurationSymbol       (void);
		bool     isMensuration             (void) { return isMensurationSymbol(); }
		bool     isOriginalMensurationSymbol(void);
		bool     isModernMensurationSymbol (void);
		bool     isOriginalMensuration     (void) { return isOriginalMensurationSymbol(); }
		bool     isModernMensuration       (void) { return isModernMensurationSymbol(); }
		bool     isInstrumentName          (void);
		bool     isInstrumentAbbreviation  (void);
		bool     isInstrumentDesignation   (void);
		bool     isInstrumentCode          (void) { return isInstrumentDesignation(); }
		bool     isInstrumentClass         (void);
		bool     isInstrumentGroup         (void);
		bool     isInstrumentNumber        (void);
		bool     isModernInstrumentName    (void);
		bool     isModernInstrumentAbbreviation(void);
		bool     isOriginalInstrumentName    (void);
		bool     isOriginalInstrumentAbbreviation(void);
		bool     isStria                   (void);

		std::string getInstrumentName        (void);
		std::string getInstrumentAbbreviation(void);

		bool     hasSlurStart              (void);
		bool     hasSlurEnd                (void);
		int      hasVisibleAccidental      (int subtokenIndex) const;
		int      hasCautionaryAccidental   (int subtokenIndex) const;
		bool     hasLigatureBegin          (void);
		bool     hasRectaLigatureBegin     (void);
		bool     hasObliquaLigatureBegin   (void);
		bool     hasLigatureEnd            (void);
		bool     hasRectaLigatureEnd       (void);
		bool     hasObliquaLigatureEnd     (void);
		char     hasStemDirection          (void);
		bool     allSameBarlineStyle       (void);


		// pitch-related functions (in HumdrumToken-midi.cpp):
		int              getMidiPitch         (void);
		void             getMidiPitches       (std::vector<int>& output);
		std::vector<int> getMidiPitches       (void);
		void             getMidiPitchesSortHL (std::vector<int>& output);
		std::vector<int> getMidiPitchesSortHL (void);
		void             getMidiPitchesSortLH (std::vector<int>& output);
		std::vector<int> getMidiPitchesSortLH (void);

		int              getMidiPitchResolveNull         (void);
		void             getMidiPitchesResolveNull       (std::vector<int>& output);
		std::vector<int> getMidiPitchesResolveNull       (void);
		void             getMidiPitchesResolveNullSortHL (std::vector<int>& output);
		std::vector<int> getMidiPitchesResolveNullSortHL (void);
		void             getMidiPitchesResolveNullSortLH (std::vector<int>& output);
		std::vector<int> getMidiPitchesResolveNullSortLH (void);

		// pitch-related functions (in HumdrumToken-base40.cpp):
		int              getBase40Pitch         (void);
		void             getBase40Pitches       (std::vector<int>& output);
		std::vector<int> getBase40Pitches       (void);
		void             getBase40PitchesSortHL (std::vector<int>& output);
		std::vector<int> getBase40PitchesSortHL (void);
		void             getBase40PitchesSortLH (std::vector<int>& output);
		std::vector<int> getBase40PitchesSortLH (void);

		int              getBase40PitchResolveNull         (void);
		void             getBase40PitchesResolveNull       (std::vector<int>& output);
		std::vector<int> getBase40PitchesResolveNull       (void);
		void             getBase40PitchesResolveNullSortHL (std::vector<int>& output);
		std::vector<int> getBase40PitchesResolveNullSortHL (void);
		void             getBase40PitchesResolveNullSortLH (std::vector<int>& output);
		std::vector<int> getBase40PitchesResolveNullSortLH (void);

		// duration-related functions:
		HumNum   getDuration               (void);
		HumNum   getDuration               (HumNum scale);
		HumNum   getTiedDuration           (void);
		HumNum   getTiedDuration           (HumNum scale);
		HumNum   getDurationNoDots         (void);
		HumNum   getDurationNoDots         (HumNum scale);
		int      getDots                   (char separator = ' ') const;

		HumNum   getDurationFromStart      (void);
		HumNum   getDurationFromStart      (HumNum scale);

		HumNum   getDurationToEnd          (void);
		HumNum   getDurationToEnd          (HumNum scale);

		HumNum   getDurationFromNoteStart  (void);
		HumNum   getDurationFromNoteStart  (HumNum scale);

		HumNum   getDurationToNoteEnd      (void);
		HumNum   getDurationToNoteEnd      (HumNum scale);

		HumNum   getDurationFromBarline    (void);
		HumNum   getDurationFromBarline    (HumNum scale);

		HumNum   getDurationToBarline      (void);
		HumNum   getDurationToBarline      (HumNum scale);

		HumNum   getBarlineDuration        (void);
		HumNum   getBarlineDuration        (HumNum scale);

		// metric-related functions:
		HumNum   getBeat                   (HumNum scale = 1);

		HLp      getOwner                  (void) const;
		HLp      getLine                   (void) const { return getOwner(); }
		bool     equalChar                 (int index, char ch) const;

		HTp      resolveNull               (void);
		HTp      resolveNullToken          (void) { return resolveNull(); }
		void     setNullResolution         (HTp resolution);
		int      getLineIndex              (void) const;
		int      getLineNumber             (void) const;
		int      getFieldIndex             (void) const;
		int      getFieldNumber            (void) const;
		int      getTokenIndex             (void) const;
		int      getTokenNumber            (void) const;
		const std::string& getDataType     (void) const;
		const std::string& getExInterp     (void) { return getDataType(); }
		bool     isDataType                (const std::string& dtype) const;
		bool     isDataTypeLike            (const std::string& dtype) const;
		bool     isKern                    (void) const;
		bool     isKernLike                (void) const;
		bool     isMens                    (void) const;
		bool     isMensLike                (void) const;
		bool     isStaffLike               (void) const { return isKernLike() || isMensLike(); }
		std::string   getSpineInfo         (void) const;
		int      getTrack                  (void) const;
		int      getSpineIndex             (void) const;
		int      getSubtrack               (void) const;
		bool     noteInLowerSubtrack       (void);
		std::string   getTrackString       (void) const;
		int      getSubtokenCount          (const std::string& separator = " ") const;
		std::string   getSubtoken          (int index,
		                                    const std::string& separator = " ") const;
		std::vector<std::string> getSubtokens (const std::string& separator = " ") const;
		void     replaceSubtoken           (int index, const std::string& newsubtok,
		                                    const std::string& separator = " ");
		void     setParameters             (HTp ptok);
		void     setParameters             (const std::string& pdata, HTp ptok = NULL);
		int      getStrandIndex            (void) const;

		int      getBeamStartElisionLevel  (int index = 0) const;
		int      getBeamEndElisionLevel    (int index = 0) const;

		int      getSlurStartElisionLevel  (int index = 0) const;
		int      getSlurEndElisionLevel    (int index = 0) const;

		int      getPhraseStartElisionLevel(int index) const;
		int      getPhraseEndElisionLevel  (int index = 0) const;

		HTp      getSlurStartToken         (int number = 1);
		int      getSlurStartNumber        (int endnumber);
		HTp      getSlurEndToken           (int number = 1);
		HTp      getPhraseStartToken       (int number = 1);
		HTp      getPhraseEndToken         (int number = 1);
		void     storeParameterSet         (void);
		bool     linkedParameterIsGlobal   (int index);
		std::ostream& printCsv             (std::ostream& out = std::cout);
		std::ostream& printXml             (std::ostream& out = std::cout, int level = 0,
		                                    const std::string& indent = "\t");
		std::ostream& printGlobalXmlParameterInfo(std::ostream& out = std::cout, int level = 0,
		                                   const std::string& indent = "\t");
		std::string   getXmlId             (const std::string& prefix = "") const;
		std::string   getXmlIdPrefix       (void) const;
		void     setText                   (const std::string& text);
		std::string   getText              (void) const;
		HTp      getExclusiveInterpretation(void);
		int      addLinkedParameterSet     (HTp token);
		int      getLinkedParameterSetCount(void);
		HumParamSet* getLinkedParameterSet (int index);
		HumParamSet* getParameterSet       (void);
		void         clearLinkInfo         (void);
		std::string getSlurLayoutParameter (const std::string& keyname, int subtokenindex = -1);
		std::string getPhraseLayoutParameter(const std::string& keyname, int subtokenindex = -1);
		std::string getLayoutParameter     (const std::string& category, const std::string& keyname,
		                                    int subtokenindex = -1);
		std::string getLayoutParameterChord(const std::string& category,
		                                    const std::string& keyname);
		std::string getLayoutParameterNote (const std::string& category,
		                                    const std::string& keyname, int subtokenindex);
		std::ostream& printXmlLinkedParameterInfo(std::ostream& out, int level, const std::string& indent);

		// layout parameter accessors
		std::string   getVisualDuration    (int subtokenindex = -1);
		std::string   getVisualDurationChord(void);
		std::string   getVisualDurationNote(int subtokenindex = -1);

		HumdrumToken& operator=            (HumdrumToken& aToken);
		HumdrumToken& operator=            (const std::string& aToken);
		HumdrumToken& operator=            (const char* aToken);

		// next/previous token functions:
		int         getNextTokenCount      (void) const;
		int         getPreviousTokenCount  (void) const;
		HTp         getNextToken           (int index = 0) const;
		HTp         getPreviousToken       (int index = 0) const;
		std::vector<HTp> getNextTokens     (void) const;
		std::vector<HTp> getPreviousTokens (void) const;
		void        insertTokenAfter       (HTp newtoken);

		// next/previous token on line:
		HTp      getNextFieldToken     (void) const;
		HTp      getPreviousFieldToken (void) const;
		HTp      getNextField          (void) const { return getNextFieldToken(); }
		HTp      getPreviousField      (void) const { return getPreviousFieldToken(); }

		int      getPreviousNonNullDataTokenCount(void);
		int      getPreviousNNDTCount      (void)
		                           { return getPreviousNonNullDataTokenCount(); }
		HTp      getPreviousNonNullDataToken(int index = 0);
		HTp      getPreviousNNDT           (int index = 0)
		                           { return getPreviousNonNullDataToken(index); }
		int      getNextNonNullDataTokenCount(void);
		int      getNextNNDTCount           (void)
		                               { return getNextNonNullDataTokenCount(); }
		HTp      getNextNonNullDataToken   (int index = 0);
		HTp      getNextNNDT               (int index = 0)
		                               { return getNextNonNullDataToken(index); }

		// slur-analysis based functions:
		HumNum   getSlurDuration           (HumNum scale = 1);

		void     setTrack                  (int aTrack, int aSubtrack);
		void     setTrack                  (int aTrack);
		void     copyStructure             (HTp token);

		// strophe related functions:
		HTp      getStrophe                (void);
		std::string getStropheLabel        (void);
		void     setStrophe                (HTp strophe);
		bool     hasStrophe                (void);
		void     clearStrophe              (void);
		bool     isStrophe                 (const std::string& label);
		int      getStropheStartIndex      (void);
		bool     isFirstStrophe            (void);
		bool     isPrimaryStrophe          (void);

	protected:
		void     setLineIndex              (int lineindex);
		void     setFieldIndex             (int fieldlindex);
		void     setSpineInfo              (const std::string& spineinfo);
		void     setSubtrack               (int aSubtrack);
		void     setSubtrackCount          (int count);
		void     setPreviousToken          (HTp aToken);
		void     setNextToken              (HTp aToken);
		void     addNextNonNullToken       (HTp token);
		void     makeForwardLink           (HumdrumToken& nextToken);
		void     makeBackwardLink          (HumdrumToken& previousToken);
		void     setOwner                  (HLp aLine);
		int      getState                  (void) const;
		void     incrementState            (void);
		void     setDuration               (const HumNum& dur);
		void     setStrandIndex            (int index);

		bool     analyzeDuration           (void);
		std::ostream& printXmlBaseInfo     (std::ostream& out = std::cout, int level = 0,
		                                    const std::string& indent = "\t");
		std::ostream& printXmlContentInfo  (std::ostream& out = std::cout, int level = 0,
		                                    const std::string& indent = "\t");
		std::ostream& printXmlStructureInfo(std::ostream& out = std::cout, int level = 0,
		                                    const std::string& indent = "\t");
		std::ostream& printXmlParameterInfo(std::ostream& out = std::cout, int level = 0,
		                                    const std::string& indent = "\t");
		std::ostream&	printXmlLinkedParameters (std::ostream& out = std::cout, int level = 0,
		                                    const std::string& indent = "\t");

	private:
		// address: The address contains information about the location of
		// the token on a HumdrumLine and in a HumdrumFile.
		HumAddress m_address;

		// duration: The duration of the token.  Non-rhythmic data types
		// will have a negative duration (which should be interpreted
		// as a zero duration--See HumdrumToken::hasRhythm()).
		// Grace note will have a zero duration, even if they have a duration
		// list in the token for a graphical display duration.
		HumNum m_duration;

		// nextTokens: This is a list of all previous tokens in the spine which
		// immediately precede this token. Typically there will be one
		// following token, but there can be two tokens if the current
		// token is *^, and there will be zero following tokens after a
		// spine terminating token (*-).
		std::vector<HTp> m_nextTokens;     // link to next token(s) in spine

		// previousTokens: Simiar to nextTokens, but for the immediately
		// follow token(s) in the data.  Typically there will be one
		// preceding token, but there can be multiple tokens when the previous
		// line has *v merge tokens for the spine.  Exclusive interpretations
		// have no tokens preceding them.
		std::vector<HTp> m_previousTokens; // link to last token(s) in spine

		// nextNonNullTokens: This is a list of non-tokens in the spine
		// that follow this one.
		std::vector<HTp> m_nextNonNullTokens;

		// previousNonNullTokens: This is a list of non-tokens in the spine
		// that preced this one.
		std::vector<HTp> m_previousNonNullTokens;

		// rhycheck: Used to perfrom HumdrumFileStructure::analyzeRhythm
		// recursively.
		int m_rhycheck;

		// strand: Used to keep track of contiguous voice connections between
		// secondary spines/tracks.  This is the 1-D strand index number
		// (not the 2-d one).
		int m_strand;

		// m_nullresolve: used to point to the token that a null token
		// refers to.
		HTp m_nullresolve;

		// m_linkedParameterTokens: List of Humdrum tokens which are parameters
		// (mostly only layout parameters at the moment).
		// Was previously called m_linkedParameters;
		std::vector<HTp> m_linkedParameterTokens;

		// m_parameterSet: A single parameter encoded in the text of the
		// token.  Was previously called m_linkedParameter.
		HumParamSet* m_parameterSet = NULL;

		// m_rhythm_analyzed: Set to true when HumdrumFile assigned duration
		bool m_rhythm_analyzed = false;

		// m_strophe: Starting point of a strophe that the token belongs to.
		// NULL means that it is not in a strophe.
		HTp m_strophe = NULL;

	friend class HumdrumLine;
	friend class HumdrumFileBase;
	friend class HumdrumFileStructure;
	friend class HumdrumFileContent;
	friend class HumdrumFile;
};


std::ostream& operator<<(std::ostream& out, const HumdrumToken& token);
std::ostream& operator<<(std::ostream& out, HTp token);

std::ostream& printSequence(std::vector<std::vector<HTp> >& sequence, std::ostream& out=std::cout);
std::ostream& printSequence(std::vector<HTp>& sequence, std::ostream& out = std::cout);



// The following options are used for get[Primary]TrackTokens:
// * OPT_PRIMARY    => only extract primary subspine/subtrack.
// * OPT_NOEMPTY    => don't include null tokens in extracted list if all
//                        extracted subspines contains null tokens.
//                        Includes null interpretations and comments as well.
// * OPT_NONULL     => don't include any null tokens in extracted list.
// * OPT_NOINTERP   => don't include interprtation tokens.
// * OPT_NOMANIP    => don't include spine manipulators (*^, *v, *x, *+,
//                        but still keep ** and *0).
// * OPT_NOCOMMENT  => don't include comment tokens.
// * OPT_NOGLOBALS  => don't include global records (global comments, reference
//                        records, and empty lines). In other words, only return
//                        a list of tokens from lines which hasSpines() it true.
// * OPT_NOREST     => don't include **kern rests.
// * OPT_NOTIE      => don't include **kern secondary tied notes.
//
// Compound options:
// * OPT_DATA      (OPT_NOMANIP | OPT_NOCOMMENT | OPT_NOGLOBAL)
//     Only data tokens (including barlines)
// * OPT_ATTACKS   (OPT_DATA | OPT_NOREST | OPT_NOTIE | OPT_NONULL)
//     Only note-attack tokens (when etracting **kern data)
//
#define OPT_PRIMARY   0x001
#define OPT_NOEMPTY   0x002
#define OPT_NONULL    0x004
#define OPT_NOINTERP  0x008
#define OPT_NOMANIP   0x010
#define OPT_NOCOMMENT 0x020
#define OPT_NOGLOBAL  0x040
#define OPT_NOREST    0x080
#define OPT_NOTIE     0x100
#define OPT_DATA      (OPT_NOMANIP | OPT_NOCOMMENT | OPT_NOGLOBAL)
#define OPT_ATTACKS   (OPT_DATA | OPT_NOREST | OPT_NOTIE | OPT_NONULL)


class TokenPair {
	public:
		TokenPair(void) { clear(); }
		~TokenPair() { clear(); }
		void clear(void) {
			first = NULL;
			last  = NULL;
		}
		HTp first;
		HTp last;
};


// HumFileAnalysis: class used to manage analysis states for a Humdrum file.

class HumFileAnalysis {
	public:
		HumFileAnalysis(void) {}
		~HumFileAnalysis() { clear(); }
		void clear(void) {
			m_structure_analyzed = false;
			m_rhythm_analyzed    = false;
			m_strands_analyzed   = false;
			m_slurs_analyzed     = false;
			m_beams_analyzed     = false;
			m_phrases_analyzed   = false;
			m_nulls_analyzed     = false;
			m_strophes_analyzed  = false;

			m_barlines_analyzed  = false;
			m_barlines_different = false;
		}

		// m_structure_analyzed: Used to keep track of whether or not
		// file structure has been analyzed.
		bool m_structure_analyzed = false;

		// m_rhythm_analyzed: Used to keep track of whether or not
		// rhythm structure has been analyzed.
		bool m_rhythm_analyzed = false;

		// m_strands_analyzed: Used to keep track of whether or not
		// file strands have been analyzed.
		bool m_strands_analyzed = false;

		// m_strophes_analyzed: Used to keep track of whether or not
		// file strands have been analyzed.
		bool m_strophes_analyzed = false;

		// m_slurs_analyzed: Used to keep track of whether or not
		// slur endpoints have been linked or not.
		bool m_slurs_analyzed = false;

		// m_phrases_analyzed: Used to keep track of whether or not
		// phrase endpoints have been linked or not.
		bool m_phrases_analyzed = false;

		// m_beams_analyzed: Used to keep track of whether or not
		// beam endpoints have been linked or not.
		bool m_beams_analyzed = false;

		// m_nulls_analyzed: Used to keep track of wheter or not
		// null tokens have been analyzed yet.
		bool m_nulls_analyzed = false;

		// m_barlines_analyzed: Used to keep track of wheter or not
		// barlines have beena analyzed yet.
		bool m_barlines_analyzed = false;
		// m_barlines_different: Set to true when the file contains
		// any barlines that are not all of the same at the same
		// times.
		bool m_barlines_different = false;
};

bool sortTokenPairsByLineIndex(const TokenPair& a, const TokenPair& b);


class HumdrumFileBase : public HumHash {
	public:
		              HumdrumFileBase          (void);
		              HumdrumFileBase          (HumdrumFileBase& infile);
		              HumdrumFileBase          (const std::string& contents);
		              HumdrumFileBase          (std::istream& contents);
		             ~HumdrumFileBase          ();

		HumdrumFileBase& operator=             (HumdrumFileBase& infile);
		bool          read                     (std::istream& contents);
		bool          read                     (const char* filename);
		bool          read                     (const std::string& filename);
		bool          readCsv                  (std::istream& contents,
		                                        const std::string& separator=",");
		bool          readCsv                  (const char* contents,
		                                        const std::string& separator=",");
		bool          readCsv                  (const std::string& contents,
		                                        const std::string& separator=",");

		bool          readString               (const char* contents);
		bool          readString               (const std::string& contents);
		bool          readStringCsv            (const char* contents,
		                                        const std::string& separator=",");
		bool          readStringCsv            (const std::string& contents,
		                                        const std::string& separator=",");
		bool          isValid                  (void);
		std::string   getParseError            (void) const;
		bool          isQuiet                  (void) const;
		void          setQuietParsing          (void);
		void          setNoisyParsing          (void);
		void          clear                    (void);
		bool          isStructureAnalyzed      (void);
		bool          isRhythmAnalyzed         (void);
		bool          areStrandsAnalyzed       (void);
		bool          areStrophesAnalyzed      (void);
		void          setFilenameFromSegment   (void);

    	template <class TYPE>
		   void       initializeArray          (std::vector<std::vector<TYPE>>& array, TYPE value);

		bool          parse                    (std::istream& contents)
		                                    { return read(contents); }
		bool          parse                    (const char* contents)
		                                    { return readString(contents); }
		bool          parse                    (const std::string& contents)
		                                    { return readString(contents); }
		bool          parseCsv                 (std::istream& contents,
		                                        const std::string& separator = ",")
		                                    { return readCsv(contents); }
		bool          parseCsv                 (const char* contents,
		                                        const std::string& separator = ",")
		                                    { return readStringCsv(contents); }
		bool          parseCsv                 (const std::string& contents,
		                                        const std::string& separator = ",")
		                                    { return readStringCsv(contents); }

		void          setXmlIdPrefix           (const std::string& value);
		std::string   getXmlIdPrefix           (void);
		void          setFilename              (const std::string& filename);
		std::string   getFilename              (void);
		std::string   getFilenameBase          (void);

		void          setSegmentLevel          (int level = 0);
		int           getSegmentLevel          (void);
		std::ostream& printSegmentLabel        (std::ostream& out);
		std::ostream& printNonemptySegmentLabel(std::ostream& out);

		HumdrumLine&  operator[]               (int index);
		HLp           getLine                  (int index);
		int           getLineCount             (void) const;
		HTp           token                    (int lineindex, int fieldindex);
		std::string   token                    (int lineindex, int fieldindex,
		                                        int subtokenindex,
		                                        const std::string& separator = " ");
		int           getMaxTrack              (void) const;
		int           getMaxTracks             (void) const { return getMaxTrack(); }
		int           getTrackCount            (void) const
		                                                { return getMaxTrack(); }
		int           getSpineCount            (void) const
		                                                { return getMaxTrack(); }
		std::vector<int> getMeasureNumbers     (void);
		int           getMeasureNumber         (int line);
		std::ostream& printSpineInfo           (std::ostream& out = std::cout);
		std::ostream& printDataTypeInfo        (std::ostream& out = std::cout);
		std::ostream& printTrackInfo           (std::ostream& out = std::cout);
		std::ostream& printCsv                 (std::ostream& out = std::cout,
		                                        const std::string& separator = ",");
		std::ostream& printFieldNumber         (int fieldnum, std::ostream& out);
		std::ostream& printFieldIndex          (int fieldind, std::ostream& out);
		void          usage                    (const std::string& command);
		void          example                  (void);

		bool          analyzeNonNullDataTokens (void);
		HTp           getTrackStart            (int track) const;
		void          getSpineStopList         (std::vector<HTp>& spinestops);
		HTp           getSpineStart            (int spine) const
		                                       { return getTrackStart(spine+1); }
		void          getSpineStartList        (std::vector<HTp>& spinestarts);
		void          getSpineStartList        (std::vector<HTp>& spinestarts,
		                                        const std::string& exinterp);
		void          getSpineStartList        (std::vector<HTp>& spinestarts,
		                                        const std::vector<std::string>& exinterps);
		void          getKernSpineStartList    (std::vector<HTp>& spinestarts);
		std::vector<HTp> getKernSpineStartList (void);
		void          getKernLikeSpineStartList(std::vector<HTp>& spinestarts);
		std::vector<HTp> getKernLikeSpineStartList(void);
		void          getStaffLikeSpineStartList(std::vector<HTp>& spinestarts);
		std::vector<HTp> getStaffLikeSpineStartList(void);
		int           getExinterpCount         (const std::string& exinterp);
		void          getTrackStartList        (std::vector<HTp>& spinestarts)
		                               { return getSpineStartList(spinestarts); }
		void          getTrackStartList        (std::vector<HTp>& spinestarts,
		                                        const std::string& exinterp)
		                     { return getSpineStartList(spinestarts, exinterp); }
		void          getTrackStartList        (std::vector<HTp>& spinestarts,
		                                        const std::vector<std::string>& exinterps)
		                    { return getSpineStartList(spinestarts, exinterps); }

		int           getTrackEndCount         (int track) const;
		HTp           getTrackEnd              (int track, int subtrack = 0) const;
		void          createLinesFromTokens    (void);
		void          generateLinesFromTokens  (void) { createLinesFromTokens(); }
		void          removeExtraTabs          (void);
		void          addExtraTabs             (void);
		std::vector<int> getTrackWidths        (void);
		void          appendLine               (const std::string& line);
		void          appendLine               (HLp line);
		void          push_back                (const std::string& line)
		                                                    { appendLine(line); }
		void          push_back                (HLp line)
		                                                    { appendLine(line); }

		void          insertLine               (int index, const std::string& line);
		void          insertLine               (int index, HLp line);

		HLp           insertNullDataLine                    (HumNum timestamp);
		HLp           insertNullInterpretationLine          (HumNum timestamp);
		HLp           insertNullInterpretationLineAbove     (HumNum timestamp);
		HLp           insertNullInterpretationLineAboveIndex(int index);
		HLp           getLineForInterpretationInsertion     (int index);
		HLp           getLineForInterpretationInsertionAbove(int index);

		void          clearTokenLinkInfo       (void);

		void          deleteLine               (int index);
//		void          adjustMergeSpineLines    (void);

		HLp           back                     (void);
		void          makeBooleanTrackList     (std::vector<bool>& spinelist,
		                                        const std::string& spinestring);


		std::vector<HLp> getReferenceRecords(void);
		std::vector<HLp> getGlobalReferenceRecords(void);
		std::vector<HLp> getUniversalReferenceRecords(void);
		std::string getReferenceRecord(const std::string& key);

		// spine analysis functionality:
		void          getTrackSequence         (std::vector<std::vector<HTp> >& sequence,
		                                        HTp starttoken, int options);
		void          getTrackSequence         (std::vector<std::vector<HTp> >& sequence,
		                                        int track, int options);
		void          getPrimaryTrackSequence  (std::vector<HTp>& sequence,
		                                        int track, int options);

		void          getSpineSequence         (std::vector<std::vector<HTp> >& sequence,
		                                        HTp starttoken, int options);
		void          getSpineSequence         (std::vector<std::vector<HTp> >& sequence,
		                                        int spine, int options);
		void          getPrimarySpineSequence  (std::vector<HTp>& sequence,
		                                        int spine, int options);

		void          getTrackSeq              (std::vector<std::vector<HTp> >& sequence,
		                                        HTp starttoken, int options)
		                     { getTrackSequence(sequence, starttoken, options); }
		void          getTrackSeq              (std::vector<std::vector<HTp> >& sequence,
		                                        int track, int options)
		                          { getTrackSequence(sequence, track, options); }
		void          getPrimaryTrackSeq       (std::vector<HTp>& sequence,
		                                        int track, int options)
		                    {getPrimaryTrackSequence(sequence, track, options); }

		// functions defined in HumdrumFileBase-net.cpp:
		static std::string getUriToUrlMapping        (const std::string& uri);
		void          readFromHumdrumUri        (const std::string& humaddress);
		void          readFromJrpUri            (const std::string& jrpaddress);
		void          readFromHttpUri           (const std::string& webaddress);
		static void   readStringFromHttpUri     (std::stringstream& inputdata,
		                                         const std::string& webaddress);

		bool          analyzeBaseFromLines     (void);
		bool          analyzeBaseFromTokens    (void);

		bool          analyzeTokens             (void);
		bool          analyzeSpines             (void);
		bool          analyzeLinks              (void);
		bool          analyzeTracks             (void);
		bool          analyzeLines              (void);

	protected:
		static int    getChunk                  (int socket_id,
		                                         std::stringstream& inputdata,
		                                         char* buffer, int bufsize);
		static int    getFixedDataSize          (int socket_id,
		                                         int datalength,
		                                         std::stringstream& inputdata,
		                                         char* buffer, int bufsize);
		static void   prepare_address           (struct sockaddr_in *address,
		                                         const std::string& hostname,
		                                         unsigned short int port);
		static int    open_network_socket       (const std::string& hostname,
		                                         unsigned short int port);

	protected:
		bool          adjustSpines              (HumdrumLine& line,
		                                         std::vector<std::string>& datatype,
		                                         std::vector<std::string>& sinfo);
		std::string   getMergedSpineInfo        (std::vector<std::string>& info,
		                                         int starti, int extra);
		bool          stitchLinesTogether       (HumdrumLine& previous,
		                                         HumdrumLine& next);
		void          addToTrackStarts          (HTp token);
		void          addUniqueTokens           (std::vector<HTp>& target,
		                                         std::vector<HTp>& source);
		bool          processNonNullDataTokensForTrackForward(HTp starttoken,
		                                         std::vector<HTp> ptokens);
		bool          processNonNullDataTokensForTrackBackward(HTp starttoken,
		                                         std::vector<HTp> ptokens);
		bool          setParseError             (std::stringstream& err);
		bool          setParseError             (const std::string& err);
		bool          setParseError             (const char* format, ...);
//		void          fixMerges                 (int linei);

	protected:

		// m_lines: an array representing lines from the input file.
		// The contents of lines must be deallocated when deconstructing object.
		std::vector<HLp> m_lines;

		// m_filename: name of the file which was loaded.
		std::string m_filename;

		// m_segementlevel: segment level (e.g., work/movement)
		int m_segmentlevel;

		// m_trackstarts: list of addresses of the exclusive interpreations
		// in the file.  The first element in the list is reserved, so the
		// number of tracks (primary spines) is equal to one less than the
		// size of this list.
		std::vector<HTp> m_trackstarts;

		// m_trackends: list of the addresses of the spine terminators in the
		// file. It is possible that spines can split and their subspines do not
		// merge before termination; therefore, the ends are stored in
		// a 2d array. The first dimension is the track number, and the second
		// dimension is the list of terminators.
		std::vector<std::vector<HTp> > m_trackends;

		// m_barlines: list of barlines in the data.  If the first measures is
		// a pickup measure, then the first entry will not point to the first
		// starting exclusive interpretation line rather than to a barline.
		std::vector<HLp> m_barlines;
		// Maybe also add "measures" which are complete metrical cycles.

		// m_ticksperquarternote: this is the number of tick
		int m_ticksperquarternote;

		// m_idprefix: an XML id prefix used to avoid id collisions when
		// including multiple HumdrumFile XML in a single group.
		std::string m_idprefix;

		// m_strands1d: one-dimensional list of spine strands.
		std::vector<TokenPair> m_strand1d;

		// m_strands2d: two-dimensional list of spine strands.
		std::vector<std::vector<TokenPair> > m_strand2d;

		// m_strophes1d: one-dimensional list of all *strophe/*Xstrophe pairs.
		std::vector<TokenPair> m_strophes1d;

		// m_strophes2d: two-dimensional list of all *strophe/*Xstrophe pairs.
		std::vector<std::vector<TokenPair> > m_strophes2d;

		// m_quietParse: Set to true if error messages should not be
		// printed to the console when reading.
		bool m_quietParse;

		// m_parseError: Set to true if a read is successful.
		std::string m_parseError;

		// m_displayError: Used to print error message only once.
		bool m_displayError;

		// m_signifiers: Used to keep track of !!!RDF records.
		HumSignifiers m_signifiers;

		// m_analysis: Used to keep track of analysis states for the file.
		HumFileAnalysis m_analyses;

	public:
		// Dummy functions to allow the HumdrumFile class's inheritance
		// to be shifted between HumdrumFileContent (the top-level default),
		// HumdrumFileStructure (mid-level interface), or HumdrumFileBase
		// (low-level interface).

		//
		// HumdrumFileStructure public functions:
		//
		bool readNoRhythm      (std::istream& infile) { return read(infile); };
		bool readNoRhythm      (const char*   filename) {return read(filename);};
		bool readNoRhythm      (const std::string& filename) {return read(filename);};
		bool readStringNoRhythm(const char*   contents) {return read(contents);};
		bool readStringNoRhythm(const std::string& contents) {return read(contents);};
		HumNum       getScoreDuration           (void) const { return 0; };
		std::ostream& printDurationInfo         (std::ostream& out=std::cout) {return out;};
		int          tpq                        (void) { return 0; }
		int          getBarlineCount            (void) const { return 0; }
		HLp          getBarline                 (int index) const { return NULL;};
		HumNum       getBarlineDuration         (int index) const { return 0; };
		HumNum       getBarlineDurationFromStart(int index) const { return 0; };
		HumNum       getBarlineDurationToEnd    (int index) const { return 0; };

		// HumdrumFileContent public functions:
		// to be added later

};

std::ostream& operator<<(std::ostream& out, HumdrumFileBase& infile);



//////////////////////////////
//
// HumdrumFileBase::initializeArray -- adjust the size of the input array
//     to the same dimensions as the HumdrumFile, filling in each cell of the
//     array with the given value as a default.
//

template <class TYPE>
void HumdrumFileBase::initializeArray(std::vector<std::vector<TYPE>>& array, TYPE value) {
	HumdrumFileBase& infile = *this;
	array.clear();
	array.resize(infile.getLineCount());
	for (int i=0; i<infile.getLineCount(); i++) {
		array[i].resize(infile[i].getFieldCount());
		fill(array[i].begin(), array[i].end(), value);
	}
}



class HumdrumFileStructure : public HumdrumFileBase {
	public:
		              HumdrumFileStructure         (void);
		              HumdrumFileStructure         (const std::string& filename);
		              HumdrumFileStructure         (std::istream& contents);
		             ~HumdrumFileStructure         ();
		bool          hasFilters                   (void);
		bool          hasGlobalFilters             (void);
		bool          hasUniversalFilters          (void);

		// TSV reading functions:
		bool          read                         (std::istream& contents);
		bool          read                         (const char* filename);
		bool          read                         (const std::string& filename);
		bool          readString                   (const char* contents);
		bool          readString                   (const std::string& contents);
		bool parse(std::istream& contents)      { return read(contents); }
		bool parse(const char* contents)   { return readString(contents); }
		bool parse(const std::string& contents) { return readString(contents); }
		bool          readNoRhythm                 (std::istream& contents);
		bool          readNoRhythm                 (const char* filename);
		bool          readNoRhythm                 (const std::string& filename);
		bool          readStringNoRhythm           (const char* contents);
		bool          readStringNoRhythm           (const std::string& contents);

		// CSV reading functions:
		bool          readCsv                      (std::istream& contents,
		                                            const std::string& separator=",");
		bool          readCsv                      (const char* filename,
		                                            const std::string& separator=",");
		bool          readCsv                      (const std::string& filename,
		                                            const std::string& separator=",");
		bool          readStringCsv                (const char* contents,
		                                            const std::string& separator=",");
		bool          readStringCsv                (const std::string& contents,
		                                            const std::string& separator=",");
		bool parseCsv(std::istream& contents, const std::string& separator = ",")
		                                 { return readCsv(contents, separator); }
		bool parseCsv(const char* contents, const std::string& separator = ",")
		                           { return readStringCsv(contents, separator); }
		bool parseCsv(const std::string& contents, const std::string& separator = ",")
		                           { return readStringCsv(contents, separator); }
		bool          readNoRhythmCsv              (std::istream& contents,
		                                            const std::string& separator = ",");
		bool          readNoRhythmCsv              (const char* filename,
		                                            const std::string& separator = ",");
		bool          readNoRhythmCsv              (const std::string& filename,
		                                            const std::string& separator = ",");
		bool          readStringNoRhythmCsv        (const char* contents,
		                                            const std::string& separator = ",");
		bool          readStringNoRhythmCsv        (const std::string& contents,
		                                            const std::string& separator = ",");

		// rhythmic analysis related functionality:
		HumNum        getScoreDuration             (void) const;
		std::ostream& printDurationInfo            (std::ostream& out = std::cout);
		int           tpq                          (void);
		int           getTpq                       (void) { return tpq(); }

		void          resolveNullTokens (void);

		// strand functionality:
		int           getStrandCount    (void);
		HTp           getStrandStart    (int index);
		HTp           getStrandBegin    (int index) { return getStrandStart(index); }
		HTp           getStrandEnd      (int index);
		HTp           getStrandStop     (int index) { return getStrandEnd(index); }
		HTp           getStrandStart    (int sindex, int index);
		HTp           getStrandBegin    (int sindex, int index) { return getStrandStart(sindex, index); }
		HTp           getStrandEnd      (int sindex, int index);
		HTp           getStrandStop     (int sindex, int index) { return getStrandEnd(sindex, index); }
		int           getStrandCount    (int spineindex);

		HTp           getStrand         (int index) { return getStrandStart(index); }
		HTp           getStrand         (int sindex, int index) { return getStrandStart(sindex, index); }

		// strophe functionality (located in src/HumdrumFileStructure-strophe.cpp)
		bool         analyzeStrophes    (void);
		void         analyzeStropheMarkers(void);
		int          getStropheCount    (void);
		int          getStropheCount    (int spineindex);
		HTp          getStropheStart    (int index);
		HTp          getStropheBegin    (int index) { return getStropheStart(index); }
		HTp          getStropheEnd      (int index);
		HTp          getStropheStop     (int index) { return getStropheStart(index); }
		HTp          getStropheStart    (int spine, int index);
		HTp          getStropheBegin    (int spine, int index) { return getStropheStart(index); }
		HTp          getStropheEnd      (int spine, int index);
		HTp          getStropheStop     (int spine, int index) { return getStropheStart(index); }

		// barline/measure functionality:
		int           getBarlineCount              (void) const;
		HLp           getBarline                   (int index) const;
		HumNum        getBarlineDuration           (int index) const;
		HumNum        getBarlineDurationFromStart  (int index) const;
		HumNum        getBarlineDurationToEnd      (int index) const;

		bool          analyzeStructure             (void);
		bool          analyzeStructureNoRhythm     (void);
		bool          analyzeRhythmStructure       (void);
		bool          analyzeStrands               (void);

		// signifier access
		std::string   getKernLinkSignifier         (void);
		std::string   getKernAboveSignifier        (void);
		std::string   getKernBelowSignifier        (void);


	protected:
		bool          analyzeRhythm                (void);
		bool          assignRhythmFromRecip        (HTp spinestart);
		bool          analyzeMeter                 (void);
		bool          analyzeTokenDurations        (void);
		bool          analyzeGlobalParameters      (void);
		bool          analyzeLocalParameters       (void);
		// bool          analyzeParameters            (void);
		bool          analyzeDurationsOfNonRhythmicSpines(void);
		HumNum        getMinDur                    (std::vector<HumNum>& durs,
		                                            std::vector<HumNum>& durstate);
		bool          getTokenDurations            (std::vector<HumNum>& durs,
		                                            int line);
		bool          cleanDurs                    (std::vector<HumNum>& durs,
		                                            int line);
		bool          decrementDurStates           (std::vector<HumNum>& durs,
		                                            HumNum linedur, int line);
		bool          assignDurationsToTrack       (HTp starttoken,
		                                            HumNum startdur);
		bool          prepareDurations             (HTp token, int state,
		                                            HumNum startdur);
		bool          setLineDurationFromStart     (HTp token, HumNum dursum);
		bool          analyzeRhythmOfFloatingSpine (HTp spinestart);
		bool          analyzeNullLineRhythms       (void);
		void          fillInNegativeStartTimes     (void);
		void          assignLineDurations          (void);
		void          assignStrandsToTokens        (void);
		std::set<HumNum> getNonZeroLineDurations   (void);
		std::set<HumNum> getPositiveLineDurations  (void);
		void          processLocalParametersForStrand(int index);
		bool          processLocalParametersForTrack (HTp starttok, HTp current);
		void          checkForLocalParameters      (HTp token, HTp current);
		bool          assignDurationsToNonRhythmicTrack(HTp endtoken, HTp ptoken);
		void          analyzeSpineStrands          (std::vector<TokenPair>& ends,
		                                            HTp starttok);
		void          analyzeSignifiers            (void);
		void          setLineRhythmAnalyzed        (void);
		bool          prepareMensurationInformation(void);
};



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



#ifndef HUMDRUMFILE_PARENT
	#define HUMDRUMFILE_PARENT HumdrumFileContent
#endif

class HumdrumFile : public HUMDRUMFILE_PARENT {
	public:
		              HumdrumFile          (void);
		              HumdrumFile          (const std::string& filename);
		              HumdrumFile          (std::istream& filename);
		             ~HumdrumFile          ();

		std::ostream& printXml             (std::ostream& out = std::cout, int level = 0,
		                                    const std::string& indent = "\t");
		std::ostream& printXmlParameterInfo(std::ostream& out, int level,
		                                    const std::string& indent);
};



//////////////////////////////
//
// MuseData line types, reference: Beyond Midi, page 410.
//

#define E_muserec_note_regular       'N'
	//                                'A' --> use type E_muserec_note_regular
	//                                'B' --> use type E_muserec_note_regular
	//                                'C' --> use type E_muserec_note_regular
	//                                'D' --> use type E_muserec_note_regular
	//                                'E' --> use type E_muserec_note_regular
	//                                'F' --> use type E_muserec_note_regular
	//                                'G' --> use type E_muserec_note_regular
#define E_muserec_note_chord         'C'
#define E_muserec_note_cue           'c'
#define E_muserec_note_grace         'g'
#define E_muserec_note_grace_chord   'G'
#define E_muserec_print_suggestion   'P'
#define E_muserec_sound_directives   'S'
#define E_muserec_end                '/'
#define E_muserec_endtext            'T'
#define E_muserec_append             'a'
#define E_muserec_backspace          'b'
#define E_muserec_back               'b'
#define E_muserec_backward           'b'
#define E_muserec_figured_harmony    'f'
#define E_muserec_rest_invisible     'i'
#define E_muserec_forward            'i'
#define E_muserec_measure            'm'
#define E_muserec_rest               'r'
#define E_muserec_musical_attributes '$'
#define E_muserec_comment_toggle     '&'
#define E_muserec_comment_line       '@'
#define E_muserec_musical_directions '*'

#define E_muserec_copyright          '1'  // reserved for copyright notice
#define E_muserec_header_1           '1'  // reserved for copyright notice

#define E_muserec_header_2           '2'  // reserved for identification
#define E_muserec_id                 '2'  // reserved for identification

#define E_muserec_header_3           '3'  // reserved

#define E_muserec_header_4           '4'  // <date> <name of encoder>
#define E_muserec_encoder            '4'  // <date> <name of encoder>

#define E_muserec_header_5           '5'  // WK#:<work number> MV#:<mvmt num>
#define E_muserec_work_info          '5'  // WK#:<work number> MV#:<mvmt num>

#define E_muserec_header_6           '6'  // <source>
#define E_muserec_source             '6'  // <source>

#define E_muserec_header_7           '7'  // <work title>
#define E_muserec_work_title         '7'  // <work title>

#define E_muserec_header_8           '8'  // <movement title>
#define E_muserec_movement_title     '8'  // <movement title>

#define E_muserec_header_9           '9'  // <name of part>
#define E_muserec_header_part_name   '9'  // <name of part>

#define E_muserec_header_10          '0'  // misc designations

#define E_muserec_header_11          'A'  // group memberships
#define E_muserec_group_memberships  'A'  // group memberships

// multiple muserec_head_12 lines can occur:
#define E_muserec_header_12          'B'  // <name1>: part <x> of <num in group>
#define E_muserec_group              'B'  // <name1>: part <x> of <num in group>

#define E_muserec_unknown            'U'  // unknown record type
#define E_muserec_empty              'E'  // nothing on line and not header or multi-line comment
#define E_muserec_deleted            'D'  // deleted line

// non-standard record types for MuseDataSet
#define E_muserec_filemarker         '+'
#define E_muserec_filename           'F'
#define E_musrec_header               1000
#define E_musrec_footer               2000


class MuseRecordBasic {
	public:
		                  MuseRecordBasic    (void);
		                  MuseRecordBasic    (const std::string& aLine, int index = -1);
		                  MuseRecordBasic    (MuseRecordBasic& aRecord);
		                 ~MuseRecordBasic    ();

		void              clear              (void);
		int               isEmpty            (void);
		void              cleanLineEnding    (void);
		std::string       extract            (int start, int stop);
		char&             getColumn          (int index);
		std::string       getColumns         (int startcol, int endcol);
		void              setColumns         (std::string& data, int startcol,
		                                      int endcol);
		int               getLength          (void) const;
		std::string       getLine            (void);
		int               getLineIndex       (void) { return m_lineindex; }
		void              setLineIndex       (int index);
		int               getLineNumber      (void) { return m_lineindex+1; }
		int               getType            (void) const;
		void              setTypeGraceNote   (void);
		void              setTypeGraceChordNote(void);
		void              setHeaderState     (int state);
		MuseData*         getOwner           (void);

		// Humdrum conversion variables
		void              setToken           (HTp token);
		HTp               getToken           (void);
		void              setVoice           (GridVoice* voice);
		GridVoice*        getVoice           (void);

		MuseRecordBasic&  operator=          (MuseRecordBasic& aRecord);
		MuseRecordBasic&  operator=          (MuseRecordBasic* aRecord);
		MuseRecordBasic&  operator=          (const std::string& aRecord);
		char&             operator[]         (int index);
		void              setLine            (const std::string& aString);
		void              setType            (int aType);
		void              shrink             (void);
		void              insertString       (int column, const std::string& strang);
		void              insertStringRight  (int column, const std::string& strang);
		void              setString          (std::string& strang);
		void              appendString       (const std::string& strang);
		void              appendInteger      (int value);
		void              appendRational     (HumNum& value);
		void              append             (const char* format, ...);

		// mark-up accessor functions:
		void              setAbsBeat         (HumNum value);
		void              setQStamp          (HumNum value);
		void              setAbsBeat         (int topval, int botval = 1);
		void              setQStamp          (int topval, int botval = 1);
		HumNum            getAbsBeat         (void);
		HumNum            getQStamp          (void);

		void              setLineDuration    (HumNum value);
		void              setLineDuration    (int topval, int botval = 1);
		HumNum            getLineDuration    (void);

		void              setNoteDuration    (HumNum value);
		void              setNoteDuration    (int topval, int botval = 1);
		HumNum            getNoteDuration    (void);
		void              setRoundedBreve    (void);

		void              setMarkupPitch     (int aPitch);
		int               getMarkupPitch     (void);

		void              setLayer           (int layer);
		int               getLayer           (void);

		// tied note functions:
		int               isTied                  (void);
		int               getLastTiedNoteLineIndex(void);
		int               getNextTiedNoteLineIndex(void);
		void              setLastTiedNoteLineIndex(int index);
		void              setNextTiedNoteLineIndex(int index);
		int               hasTieGroupStart        (void);
		int               isNoteAttack            (void);
		/* HumNum            getTiedNoteDuration     (void); */

		std::string       getLayoutVis       (void);

		// boolean type fuctions:
		bool              isAnyNote          (void);
		bool              isRest             (void);
		bool              isAnyNoteOrRest    (void);
		bool              isAttributes       (void); // starts with $
		bool              isAttribute        (void) { return isAttributes(); }
		bool              isBackup           (void);
		bool              isBarline          (void);
		bool              isMeasure          (void) { return isBarline(); }
		bool              isBodyRecord       (void);
		bool              isChordGraceNote   (void);
		bool              isChordNote        (void);
		bool              isDirection        (void); // starts with "*"
		bool              isMusicalDirection (void); // starts with "*"
		bool              isAnyComment       (void); // starts with "@" or between lines starting with &.
		bool              isLineComment      (void); // starts with "@"
		bool              isBlockComment     (void); // lines between lines starting with &.
		bool              isCopyright        (void); // 1st non-comment line in file
		bool              isCueNote          (void); // starts with "c"
		bool              isEncoder          (void); // 4th non-comment line in file
		bool              isFiguredHarmony   (void); // starts with "f"
		bool              isGraceNote        (void); // starts with "g"
		bool              isGroup            (void);
		bool              isGroupMembership  (void);
		bool              isHeaderRecord     (void);
		bool              isId               (void);
		bool              isMovementTitle    (void);
		bool              isPartName         (void);
		bool              isRegularNote      (void);
		bool              isAnyRest          (void);
		bool              isRegularRest      (void);
		bool              isInvisibleRest    (void);
		bool              isPrintSuggestion  (void);  // starts with "P"
		bool              isSource           (void);
		bool              isWorkInfo         (void);
		bool              isWorkTitle        (void);
		bool              hasTpq             (void);
		int               getTpq             (void);
		void              setTpq             (int value);
		static std::string musedataToUtf8    (std::string& input);


	protected:
		std::string       m_recordString;     // actual characters on line

		std::vector<int>  m_printSuggestions; // print suggestions for this line (if applicable)
		                                      // print suggestions start with the letter "P" and
                                            // follow a note/rest line, as well as musical
		                                      // direction lines that start with "*".  The value
		                                      // int the difference in indexes between the current
		                                      //  line and the print suggestion (typically +1).

      std::vector<int> m_musicalDirections; // Musical directions associated with this line
		                                      // (if applicable) stored as delta indexes.  Musical
		                                      // direction lines start with "*" and are used for
		                                      // dynamics, hairpins, etc.  Typically -1 from a note
		                                      // or -2 if there is a print suggestion for the musical
		                                      // direction.

		// mark-up data for the line:
		int               m_lineindex;        // index into original file
		int               m_type;             // category of MuseRecordBasic record
		HumNum            m_qstamp;           // dur in quarter notes from start
		HumNum            m_lineduration;     // duration of line
		HumNum            m_noteduration;     // duration of note

		int               m_b40pitch;         // base 40 pitch
		int               m_nexttiednote;     // line number of next note tied to
		                                      // this one (-1 if no tied note)
		int               m_lasttiednote;     // line number of previous note tied
		                                      // to this one (-1 if no tied note)
		int               m_roundBreve;
		int               m_header = -1;      // -1 = undefined, 0 = no, 1 = yes
		int               m_layer = 0;        // voice/layer (track info but may be analyzed)
		int               m_tpq = 0;          // ticks-per-quarter for durations
		std::string       m_graphicrecip;     // graphical duration of note/rest
		GridVoice*			m_voice = NULL;     // conversion structure that token is stored in.
		MuseData*         m_owner = NULL;

		void              setOwner    (MuseData* owner);

	public:
		static std::string       trimSpaces         (std::string input);

		friend class MuseRecord;
		friend class MuseData;
};


std::ostream& operator<<(std::ostream& out, MuseRecordBasic& aRecord);
std::ostream& operator<<(std::ostream& out, MuseRecordBasic* aRecord);





class MuseRecord : public MuseRecordBasic {
	public:
		            MuseRecord                  (void);
		            MuseRecord                  (const std::string& aLine);
		            MuseRecord                  (MuseRecord& aRecord);
		           ~MuseRecord                  ();

		MuseRecord& operator=                   (MuseRecord& aRecord);


	// MuseData part header information:
		std::string getPartName();


	//////////////////////////////
	//
	// functions which process regular notes (A-G), cue notes (c), grace notes (g),
	//     and chords (" ").  Definitions stored in MuseRecord-note.cpp.
	//
		// columns 1-5: pitch field information
		std::string      getNoteField                 (void);
		int              getOctave                    (void);
		std::string      getOctaveString              (void);
		int              getPitch                     (void);
		std::string      getPitchString               (void);
		int              getPitchClass                (void);
		std::string      getPitchClassString          (void);
		int              getAccidental                (void);
		std::string      getAccidentalString          (void);
		int              getBase40                    (void);
		void             setPitch                     (int base40, int chordnote = 0,
		                                               int gracenote = 0);
		void             setPitch                     (const std::string& pitchname);
		void             setPitchAtIndex              (int index,
		                                               const std::string& pitchname);
		void             setChordPitch                (const std::string& pitchname);
		void             setGracePitch                (const std::string& pitchname);
		void             setGraceChordPitch           (const std::string& pitchname);
		void             setCuePitch                  (const std::string& pitchname);
		void             setStemDown                  (void);
		void             setStemUp                    (void);

		// columns 6-9: duration field information
		std::string      getTickDurationField         (void);
		std::string      getTickDurationString        (void);
		int              getTickDuration              (void);
		int              getLineTickDuration          (void);
		int              getNoteTickDuration          (void);
		std::string      getTieString                 (void);
		int              getTie                       (void);
		int              setTie                       (int hidden = 0);
		int              tieQ                         (void);
		int              getTicks                     (void);
		void             setTicks                     (int value);
		void             setBack                      (int value);
		void             setDots                      (int value);
		int              getDotCount                  (void);
		void             setNoteheadShape             (HumNum duration);
		void             setNoteheadShapeMensural     (HumNum duration);
		void             setNoteheadMaxima            (void);
		void             setNoteheadLong              (void);
		void             setNoteheadBreve             (void);
		void             setNoteheadBreveSquare       (void);
		void             setNoteheadBreveRound        (void);

		void             setNoteheadWhole             (void);
		void             setNoteheadHalf              (void);
		void             setNoteheadQuarter           (void);
		void             setNotehead8th               (void);
		void             setNotehead16th              (void);
		void             setNotehead32nd              (void);
		void             setNotehead64th              (void);
		void             setNotehead128th             (void);
		void             setNotehead256th             (void);

		void             setNoteheadBreveMensural     (void);
		void             setNoteheadWholeMensural     (void);
		void             setNoteheadHalfMensural      (void);
		void             setNoteheadQuarterMensural   (void);
		void             setNotehead8thMensural       (void);
		void             setNotehead16thMensural      (void);
		void             setNotehead32ndMensural      (void);
		void             setNotehead64thMensural      (void);
		void             setNotehead128thMensural     (void);
		void             setNotehead256thMensural     (void);

		// columns 10-12 ---> blank

		// columns 13-80: graphical and interpretive information

		// column 13: footnote flag
		std::string      getFootnoteFlagField         (void);
		std::string      getFootnoteFlagString        (void);
		int              getFootnoteFlag              (void);
		int              footnoteFlagQ                (void);

		// column 14: level number
		std::string      getLevelField                (void);
		std::string      getLevelString               (void);
		int              getLevel                     (void);
		int              levelQ                       (void);

		// column 15: track number
		std::string      getTrackField                (void);
		std::string      getTrackString               (void);
		int              getTrack                     (void);
		int              trackQ                       (void);

		// column 16 ---> blank

		// column 17: graphic note type
		std::string      getGraphicNoteTypeField      (void);
		std::string      getGraphicNoteTypeString     (void);
		int              getGraphicNoteType           (void);
		int              getGraphicNoteTypeSize       (void);
		int              graphicNoteTypeQ             (void);
		std::string      getGraphicRecip              (void);

		// column 18: dots of prolongation
		std::string      getProlongationField         (void);
		std::string      getProlongationString        (void);
		int              getProlongation              (void);
		std::string      getStringProlongation        (void);
		int              prolongationQ                (void);

		// column 19: notated accidentals
		std::string      getNotatedAccidentalField    (void);
		std::string      getNotatedAccidentalString   (void);
		int              getNotatedAccidental         (void);
		int              notatedAccidentalQ           (void);

		// columns 20-22: time modification
		std::string      getTimeModificationField     (void);
		std::string      getTimeModificationString    (void);
		HumNum           getTimeModification          (void);
		std::string      getTimeModificationLeftField (void);
		std::string      getTimeModificationLeftString(void);
		int              getTimeModificationLeft      (void);
		std::string      getTimeModificationRightField(void);
		std::string      getTimeModificationRightString(void);
		int              getTimeModificationRight     (void);
		bool             timeModificationQ            (void);
		bool             timeModificationLeftQ        (void);
		bool             timeModificationRightQ       (void);

		// column 23: stem direction
		std::string      getStemDirectionField        (void);
		std::string      getStemDirectionString       (void);
		int              getStemDirection             (void);
		int              stemDirectionQ               (void);

		// column 24: staff number for multi-staff parts
		std::string      getStaffField                (void);
		std::string      getStaffString               (void);
		int              getStaff                     (void);
		int              staffQ                       (void);

		// column 25: blank

		// columns 26-31: beaming
		std::string      getBeamField                 (void);
		int              beamQ                        (void);
		char             getBeam8                     (void);
		char             getBeam16                    (void);
		char             getBeam32                    (void);
		char             getBeam64                    (void);
		char             getBeam128                   (void);
		char             getBeam256                   (void);
		int              beam8Q                       (void);
		int              beam16Q                      (void);
		int              beam32Q                      (void);
		int              beam64Q                      (void);
		int              beam128Q                     (void);
		int              beam256Q                     (void);
		void             setBeamInfo                  (std::string& strang);

		// columns 32-43: additional notation
		std::string      getAdditionalNotationsField  (void); // merge with below
		std::string      getOtherNotations            (void); // merge with above
		int              hasFermata                   (void);
		int              additionalNotationsQ         (void);
		int              getAddCount                  (void);
		std::string      getAddItem                   (int elementIndex);
		int              addAdditionalNotation        (char symbol);
		int              addAdditionalNotation        (const std::string& symbol);
		int              getAddItemLevel              (int elementIndex);
		std::string      getEditorialLevels           (void);
		int              addEditorialLevelQ           (void);
		//  protected:   getAddElementIndex
		int              findField                    (const std::string& key);
		int              findField                    (char key, int mincol,
		                                               int maxcol);
		// int           getNotationLevel
		int              getSlurStartColumn           (void);
		std::string      getSlurParameterRegion       (void);
		void             getSlurInfo                  (std::string& slurstarts, std::string& slurends);


		// columns 44-80: text underlay
		std::string      getTextUnderlayField         (void);
		int              textUnderlayQ                (void);
		int              getVerseCount                (void);
		std::string      getVerse                     (int index);
		std::string      getVerseUtf8                 (int index);



	//////////////////////////////
	//
	// functions which work with basso continuo figuration records ('f'), definitions
	//     stored in MuseRecord-figure.cpp
	//
		// column 2: number of figure fields
		std::string      getFigureCountField          (void);
		std::string      getFigureCountString         (void);
		int              getFigureCount               (void);

		// columns 3-5: blank

		// columns 6-8: figure division pointer advancement (duration)
		// this is the offset to the next figure and is not part
		// of the note pointer advancement
		std::string      getFigurePointerField        (void);
		std::string      getFigurePointer             (void);
		int              figurePointerQ               (void);
		int              getFigureDuration            (void);


		// columns 9-12: blank

		// columns 13-15: footnote and level information
		// column 13: footnote: uses same functions as note records in col 13.
		// column 14: level: uses same functions as note records on column 14.
		// column 15: blank

		// columns 17-80: figure fields
		std::string      getFigureFields              (void);
		std::string      getFigureString              (void);
		int              figureFieldsQ                (void);
		std::string      getFigure                    (int index = 0);



	//////////////////////////////
	//
	// functions that work with combined records ('b', 'i'):
	//



	//////////////////////////////
	//
	// functions which work with measure records ('m'), definitions stored
	//    in MuseRecord-measure.cpp.
	//
		// columns 1-7: measure style information
		std::string      getMeasureType               (void);

		// columns 9-12: measure number (left justified)
		std::string      getMeasureNumberField        (void);
		std::string      getMeasureNumber             (void);
		bool             measureNumberQ               (void);

		// columns 17-80: measure flags
		std::string      getMeasureFlags              (void);
		int              measureFermataQ              (void);
		bool             measureFlagEqual             (const std::string& key);
		void             addMeasureFlag               (const std::string& strang);



	//////////////////////////////
	//
	// Notation Attributes: functions which process musical attributes records ('$'),
	//    definitions stored in MuseRecord-attributes.cpp.
	//

		std::string      getAttributes                (void);
		void             getAttributeMap              (std::map<std::string, std::string>& amap);
		int              attributeQ                   (const std::string& attribute);
		int              getAttributeInt              (char attribute);
		int              getAttributeField            (std::string& output, const std::string& attribute);



	//////////////////////////////
	//
	// functions which work with musical direction records ('*'),
	//     definitions stored in MuseRecord-directions.cpp.
	//
		// columns 17-18: type of direction
		std::string      getDirectionTypeField        (void);
		std::string      getDirectionTypeString       (void);
		bool             isDashStart                  (void);
		bool             isDashStop                   (void);
		bool             isDynamic                    (void);
		bool             isHairpin                    (void);
		bool             isHairpinStart               (void);
		bool             isHairpinStop                (void);
		bool             isOctaveUpStart              (void);
		bool             isOctaveDownStart            (void);
		bool             isOctaveStop                 (void);
		bool             isPedalStart                 (void);
		bool             isPedalEnd                   (void);
		bool             isRehearsal                  (void);
		bool             isTextDirection              (void);

		std::string      getDirectionText             (void);
		std::string      getTextDirection             (void) { return getDirectionText(); }

		// Musical Directions: Lines starting with *
		// Functions stored in src/MuseRecordBasic-directions.cpp
		void             addMusicDirection           (int deltaIndex);
		std::string      getDirectionAsciiCharacters (void);
		bool             hasMusicalDirection         (void);
		MuseRecord*      getMusicalDirection         (int index = 0);
		std::string      getDynamicText              (void);
		MuseRecord*      getDirectionRecord          (int deltaIndex);
		std::string      getDirectionType            (void);



	//////////////////////////////
	//
	// Print Suggestings: Lines starting with "P".  Definititions stored
	//     in MuseRecord-suggestions.cpp.
	//

		void             addPrintSuggestion           (int deltaIndex);
		bool             hasPrintSuggestions          (void);
		void             getAllPrintSuggestions       (std::vector<std::string>& suggestions);
		void             getPrintSuggestions          (std::vector<std::string>& suggestions, int column);



	//////////////////////////////
	//
	// Humdrum conversion related functions, store in MuseRecord-humdrum.cpp:
	//

		std::string      getKernMeasure               (void);
		std::string      getKernBeamStyle             (void);
		std::string      getKernNoteStyle             (int beams = 0, int stems = 0);
		std::string      getKernNoteAccents           (void);
		std::string      getKernNoteOtherNotations    (void);
		std::string      getKernRestStyle             (void);


	//
	//////////////////////////////

	protected:
		void             allowNotesOnly               (const std::string& functionName);
		void             allowNotesAndRestsOnly       (const std::string& functionName);
		void             allowMeasuresOnly            (const std::string& functioName);
		void             allowFigurationOnly          (const std::string& functioName);
		void             allowFigurationAndNotesOnly  (const std::string& functioName);
		void             allowDirectionsOnly          (const std::string& functioName);
		int              getAddElementIndex           (int& index, std::string& output,
		                                               const std::string& input);
		void             zerase                       (std::string& inout, int num);
};




// A MuseEventSet is a timestamp and then a list of pointers to all
// lines in the original file that occur at that time.
// The MuseData class contains a variable called "sequence" which is
// a list of MuseEventSet object pointers which are sorted by time.

class MuseEventSet {
	public:
		                   MuseEventSet       (void);
		                   MuseEventSet       (const MuseEventSet& aSet);
		                   MuseEventSet       (HumNum atime);
		                  ~MuseEventSet       ()     { clear(); }

		void               clear              (void);
		void               setTime            (HumNum abstime);
		HumNum             getTime            (void);
		void               appendRecord       (MuseRecord* arecord);
		MuseRecord&        operator[]         (int index);
		MuseEventSet       operator=          (MuseEventSet& anevent);
		int                getEventCount      (void);

	protected:
		HumNum     absbeat;              // starting time of events
		std::vector<MuseRecord*> events; // list of events on absbeat
};



class MuseData {
	public:
		                  MuseData            (void);
		                  MuseData            (MuseData& input);
		                 ~MuseData            ();

		void              setFilename         (const std::string& filename);
		std::string       getFilename         (void);
		int               isMember            (const std::string& mstring);
		int               getMembershipPartNumber(const std::string& mstring);
		void              selectMembership    (const std::string& selectstring);
		MuseData&         operator=           (MuseData& input);
		int               getLineCount        (void);
		int               getNumLines         (void) { return getLineCount(); }
		MuseRecord&       last                (void);
		int               isEmpty             (void);
		int               append              (MuseRecord& arecord);
		int               append              (MuseData& musedata);
		int               append              (std::string& charstring);
		void              insert              (int index, MuseRecord& arecord);
		void              clear               (void);
		int               getInitialTpq       (void);

		int               read                (std::istream& input);
		int               readString          (const std::string& filename);
		int               readFile            (const std::string& filename);
		void              analyzeLayers       (void);
		int               analyzeLayersInMeasure(int startindex);
		std::string       getMeasureNumber    (int index);
		bool              measureHasData      (int index);
		bool              hasMeasureData      (int index) { return measureHasData(index); }
		int               getNextMeasureIndex (int index);

		// aliases for access to MuseRecord objects based on line indexes:
		std::string       getLine             (int index);

		bool              isCopyright         (int index);
		bool              isEncoder           (int index);
		bool              isId                (int index);
		bool              isMovementTitle     (int index);
		bool              isAnyNote           (int index);
		bool              isRegularNote       (int index);
		bool              isPartName          (int index);
		bool              isSource            (int index);
		bool              isWorkInfo          (int index);
		bool              isWorkTitle         (int index);
		bool              isHeaderRecord      (int index);
		bool              isBodyRecord        (int index);

		// header information
		std::string       getComposer         (void);
		std::string       getComposerDate     (void);
		std::string       getCopyright        (void);
		std::string       getEncoder          (void);
		std::string       getEncoderDate      (void);
		std::string       getEncoderName      (void);
		std::string       getPartName         (void);
		std::string       getId               (void);
		std::string       getMovementTitle    (void);
		std::string       getSource           (void);
		std::string       getWorkInfo         (void);
		std::string       getWorkTitle        (void);
		std::string       getOpus             (void);
		std::string       getNumber           (void);
		std::string       getMovementNumber   (void);

		// additional mark-up analysis functions for post-processing:
		void              doAnalyses          (void);
		void              analyzeType         (void);
		void              analyzeRhythm       (void);
		void              analyzeTies         (void);
		void              analyzePitch        (void);
		void              analyzeTpq          (void);

		// line-based (file-order indexing) accessor functions:
		MuseRecord&       operator[]          (int lindex);
		MuseRecord&       getRecord           (int lindex);
		MuseRecord*       getRecordPointer    (int lindex);
		HumNum            getTiedDuration     (int lindex);

		HumNum            getAbsBeat         (int lindex);
		HumNum            getQStamp          (int lindex);
		HumNum            getFileDuration    (void);

		int               getLineTickDuration (int lindex);

		// event-based (time-order indexing) accessor functions:
		MuseEventSet&     getEvent            (int eindex);
		int               getEventCount       (void);
		HumNum            getEventTime        (int eindex);
		MuseRecord&       getRecord           (int eindex, int erecord);
		int               getLineIndex        (int eindex, int erecord);
		HumNum            getLineDuration     (int eindex, int erecord);
		HumNum            getNoteDuration     (int eindex, int erecord);
		int               getLastTiedNoteLineIndex(int eindex, int erecord);
		int               getNextTiedNoteLineIndex(int eindex, int erecord);
		HumNum            getTiedDuration     (int eindex, int erecord);
		int               getType             (int eindex, int erecord);
		void              cleanLineEndings    (void);
		std::string       getError            (void);
		bool              hasError            (void);

	private:
		std::vector<MuseRecord*>    m_data;
		std::vector<MuseEventSet*>  m_sequence;
		std::string                 m_name;
		std::string                 m_error;

	protected:
		void         clearError           (void);
		void         setError             (const std::string& error);
		void         processTie           (int eventindex, int recordindex,
		                                        int lastindex);
		int          searchForPitch       (int eventindex, int b40, int track);
		int          getNextEventIndex    (int startindex, HumNum target);
		void         constructTimeSequence(void);
		void         insertEventBackwards (HumNum atime, MuseRecord* arecord);
		int          getPartNameIndex     (void);
		void         assignHeaderBodyState(void);
		void         linkPrintSuggestions (void);
		void         linkMusicDirections  (void);

	public:
		static std::string  trimSpaces    (const std::string& input);
		static std::string  convertAccents(const std::string& input);
		static std::string  cleanString   (const std::string& input);
};


std::ostream& operator<<(std::ostream& out, MuseData& musedata);




class MuseDataSet {
	public:
		                  MuseDataSet         (void);
		                  MuseDataSet         (MuseDataSet& input);
		                 ~MuseDataSet         () { clear(); }

		void              clear               (void);
		int               readPartFile        (const std::string& filename);
		int               readPartString      (const std::string& data);
		int               readPart            (std::istream& input);
		int               readFile            (const std::string& filename);
		int               readString          (const std::string& data);
		int               readString          (std::istream& input);
		int               readString          (std::stringstream& input);
		int               read                (std::istream& input);
		MuseData&         operator[]          (int index);
		int               getFileCount        (void);
		void              deletePart          (int index);
		void              cleanLineEndings    (void);
		std::vector<int>  getGroupIndexList   (const std::string& group);
		int               appendPart          (MuseData* musedata);

		std::string       getError            (void);
		bool              hasError            (void);
		void              clearError          (void);

		// MIDI related information
		double            getMidiTempo        (void);


	private:
		std::vector<MuseData*>  m_part;
		std::string             m_error;

	protected:
		void              analyzeSetType      (std::vector<int>& types,
		                                       std::vector<std::string>& lines);
		void              analyzePartSegments (std::vector<int>& startindex,
		                                       std::vector<int>& stopindex,
		                                       std::vector<std::string>& lines);
		void              setError            (const std::string& error);

};


std::ostream& operator<<(std::ostream& out, MuseDataSet& musedata);



#define GRIDREST NAN

class NoteGrid;


class NoteCell {
	public:
		       NoteCell             (NoteGrid* owner, HTp token);
		      ~NoteCell             (void) { clear();                    }

		double getSgnDiatonicPitch  (void) { return m_b7;                }
		double getSgnMidiPitch      (void) { return m_b12;               }
		double getSgnBase40Pitch    (void) { return m_b40;               }
		double getSgnAccidental     (void) { return m_accidental;        }

		double getSgnDiatonicPitchClass(void);
		double getAbsDiatonicPitchClass(void);

		double getSgnBase40PitchClass(void);
		double getAbsBase40PitchClass(void);

		double getAbsDiatonicPitch  (void) { return fabs(m_b7);          }
		double getAbsMidiPitch      (void) { return fabs(m_b12);         }
		double getAbsBase40Pitch    (void) { return fabs(m_b40);         }
		double getAbsAccidental     (void) { return fabs(m_accidental);  }

		HTp    getToken             (void) { return m_token;             }
		int    getNextAttackIndex   (void) { return m_nextAttackIndex;   }
		int    getPrevAttackIndex   (void) { return m_prevAttackIndex;   }
		int    getCurrAttackIndex   (void) { return m_currAttackIndex;   }
		int    getSliceIndex        (void) { return m_timeslice;         }
		int    getVoiceIndex        (void) { return m_voice;             }

		bool   isAttack             (void);
		bool   isRest               (void);
		bool   isSustained          (void);

		std::string getAbsKernPitch (void);
		std::string getSgnKernPitch (void);

		double operator-            (NoteCell& B);
		double operator-            (int B);

		int    getLineIndex         (void);
		int    getFieldIndex        (void);
		std::ostream& printNoteInfo (std::ostream& out);
		double getDiatonicIntervalToNextAttack      (void);
		double getDiatonicIntervalFromPreviousAttack(void);
		double getMetricLevel       (void);
		HumNum getDurationFromStart (void);
		HumNum getDuration          (void);
		void   setMeter             (int topval, HumNum botval);
		int    getMeterTop          (void);
		HumNum getMeterBottom       (void);

		std::vector<HTp> m_tiedtokens;  // list of tied notes/rests after note attack

	protected:
		void clear                  (void);
		void calculateNumericPitches(void);
		void setVoiceIndex          (int index) { m_voice = index;           }
		void setSliceIndex          (int index) { m_timeslice = index;       }
		void setNextAttackIndex     (int index) { m_nextAttackIndex = index; }
		void setPrevAttackIndex     (int index) { m_prevAttackIndex = index; }
		void setCurrAttackIndex     (int index) { m_currAttackIndex = index; }

	private:
		NoteGrid* m_owner; // the NoteGrid to which this cell belongs.
		HTp m_token;       // pointer to the note in the origina Humdrum file.
		int m_voice;       // index of the voice in the score the note belongs
		                   // 0=bottom voice (HumdrumFile ordering of parts)
		                   // column in NoteGrid.
		int m_timeslice;   // index for the row in NoteGrid.

		double m_b7;         // diatonic note number; NaN=rest; negative=sustain.
		double m_b12;        // MIDI note number; NaN=rest; negative=sustain.
		double m_b40;        // base-40 note number; NaN=rest; negative=sustain.
		double m_accidental; // chromatic alteration of a diatonic pitch.
		                     // NaN=no accidental.
		int m_nextAttackIndex; // index to next note attack (or rest),
		                       // -1 for undefined (interpred as rest).
		int m_prevAttackIndex; // index to previous note attack.
		int m_currAttackIndex; // index to current note attack (useful for
		                       // finding the start of a sustained note.
		int m_metertop = 0;    // top number of prevailing meter signature
		HumNum m_meterbot = 0; // bottom number of prevailing meter signature

	friend NoteGrid;
};



class NoteGrid {
	public:
		           NoteGrid              (void) { }
		           NoteGrid              (HumdrumFile& infile);
		          ~NoteGrid              ();

		void       clear                 (void);

		bool       load                  (HumdrumFile& infile);
		NoteCell*  cell                  (int voiceindex, int sliceindex);
		int        getVoiceCount         (void);
		int        getSliceCount         (void);
		int        getLineIndex          (int sindex);
		int        getFieldIndex         (int vindex);

		void       printDiatonicGrid     (ostream& out);
		void       printMidiGrid         (ostream& out);
		void       printBase40Grid       (ostream& out);
		void       printRawGrid          (ostream& out);
		void       printKernGrid         (ostream& out);

		double     getSgnDiatonicPitch   (int vindex, int sindex);
		double     getSgnMidiPitch       (int vindex, int sindex);
		double     getSgnBase40Pitch     (int vindex, int sindex);
		string     getSgnKernPitch       (int vindex, int sindex);

		double     getAbsDiatonicPitch   (int vindex, int sindex);
		double     getAbsMidiPitch       (int vindex, int sindex);
		double     getAbsBase40Pitch     (int vindex, int sindex);
		string     getAbsKernPitch       (int vindex, int sindex);

		bool       isRest                (int vindex, int sindex);
		bool       isSustained           (int vindex, int sindex);
		bool       isAttack              (int vindex, int sindex);

		HTp        getToken              (int vindex, int sindex);

		int        getPrevAttackDiatonic (int vindex, int sindex);
		int        getNextAttackDiatonic (int vindex, int sindex);

		void       printGridInfo         (ostream& out);
		void       printVoiceInfo        (ostream& out, int vindex);

		void       getNoteAndRestAttacks (vector<NoteCell*>& attacks, int vindex);
		double     getMetricLevel        (int sindex);
		HumNum     getNoteDuration       (int vindex, int sindex);

	protected:
		void       buildAttackIndexes    (void);
		void       buildAttackIndex      (int vindex);

	private:
		vector<vector<NoteCell*> > m_grid;
		vector<HTp>                m_kernspines;
		vector<double>             m_metriclevels;
		HumdrumFile*               m_infile;
};



class Convert {
	public:

		// Rhythm processing, defined in Convert-rhythm.cpp
		static HumNum  recipToDuration      (const std::string& recip,
		                                     HumNum scale = 4,
		                                     const std::string& separator = " ");
		static HumNum  recipToDuration      (std::string* recip,
		                                     HumNum scale = 4,
		                                     const std::string& separator = " ");
		static HumNum  recipToDurationIgnoreGrace(const std::string& recip,
		                                     HumNum scale = 4,
		                                     const std::string& separator = " ");
		static HumNum  recipToDurationIgnoreGrace(std::string* recip,
		                                     HumNum scale = 4,
		                                     const std::string& separator = " ");
		static HumNum  recipToDurationNoDots(const std::string& recip,
		                                     HumNum scale = 4,
		                                     const std::string& separator = " ");
		static HumNum  recipToDurationNoDots(std::string* recip,
		                                     HumNum scale = 4,
		                                     const std::string& separator = " ");
		static std::string  durationToRecip      (HumNum duration,
		                                     HumNum scale = HumNum(1,4));
		static std::string  durationFloatToRecip (double duration,
		                                     HumNum scale = HumNum(1,4));
		static HumNum timeSigToDurationInQuarters(HTp token);

		// Tempo processing, defined in Convert-tempo.cpp
		static int tempoNameToMm (const std::string& name, int bot = 4, int top = 4);

		// Pitch processing, defined in Convert-pitch.cpp
		static std::string  base40ToKern    (int b40);
		static int     base40ToAccidental   (int b40);
		static int     base40ToDiatonic     (int b40);
		static int     base40ToMidiNoteNumber(int b40);
		static std::string  base40ToIntervalAbbr (int b40);
		static int     kernToOctaveNumber   (const std::string& kerndata);
		static int     kernToOctaveNumber   (HTp token)
				{ return kernToOctaveNumber((std::string)*token); }
		static int     kernToAccidentalCount(const std::string& kerndata);
		static int     kernToAccidentalCount(HTp token)
				{ return kernToAccidentalCount((std::string)*token); }

      static int     kernToStaffLocation  (HTp token, HTp clef = NULL);
      static int     kernToStaffLocation  (HTp token, const std::string& clef);
      static int     kernToStaffLocation  (const std::string& token, const std::string& clef = "");

		static int     kernToDiatonicPC     (const std::string& kerndata);
		static int     kernToDiatonicPC     (HTp token)
				{ return kernToDiatonicPC     ((std::string)*token); }
		static char    kernToDiatonicUC     (const std::string& kerndata);
		static int     kernToDiatonicUC     (HTp token)
				{ return kernToDiatonicUC     ((std::string)*token); }
		static char    kernToDiatonicLC     (const std::string& kerndata);
		static int     kernToDiatonicLC     (HTp token)
				{ return kernToDiatonicLC     ((std::string)*token); }
		static int     kernToBase40PC       (const std::string& kerndata);
		static int     kernToBase40PC       (HTp token)
				{ return kernToBase40PC       ((std::string)*token); }
		static int     kernToBase12PC       (const std::string& kerndata);
		static int     kernToBase12PC       (HTp token)
				{ return kernToBase12PC       ((std::string)*token); }
		static int     kernToBase7PC        (const std::string& kerndata) {
		                                     return kernToDiatonicPC(kerndata); }
		static int     kernToBase7PC        (HTp token)
				{ return kernToBase7PC        ((std::string)*token); }
		static int     kernToBase40         (const std::string& kerndata);
		static int     kernToBase40         (HTp token)
				{ return kernToBase40         ((std::string)*token); }
		static int     kernToBase12         (const std::string& kerndata);
		static int     kernToBase12         (HTp token)
				{ return kernToBase12         ((std::string)*token); }
		static int     kernToBase7          (const std::string& kerndata);
		static int     kernToBase7          (HTp token)
				{ return kernToBase7          ((std::string)*token); }
		static std::string  kernToRecip     (const std::string& kerndata);
		static std::string  kernToRecip     (HTp token);
      static std::string base12ToKern     (int aPitch);
      static std::string base12ToPitch    (int aPitch);
      static int         base12ToBase40   (int aPitch);
		static int     kernToMidiNoteNumber (const std::string& kerndata);
		static int     kernToMidiNoteNumber(HTp token)
				{ return kernToMidiNoteNumber((std::string)*token); }
		static std::string  kernToScientificPitch(const std::string& kerndata,
		                                     std::string flat = "b",
		                                     std::string sharp = "#",
		                                     std::string separator = "");
		static std::string  kernToSciPitch  (const std::string& kerndata,
		      										 std::string flat = "b",
		                                     std::string sharp = "#",
		                                     std::string separator = "")
	       { return kernToScientificPitch(kerndata, flat, sharp, separator); }
		static std::string  kernToSP        (const std::string& kerndata,
		                                     std::string flat = "b",
		                                     std::string sharp = "#",
		                                     std::string separator = "")
		      { return kernToScientificPitch(kerndata, flat, sharp, separator); }
		static int     pitchToWbh           (int dpc, int acc, int octave,
		                                     int maxacc);
		static void    wbhToPitch           (int& dpc, int& acc, int& octave,
		                                     int maxacc, int wbh);
		static int     kernClefToBaseline   (const std::string& input);
		static int     kernClefToBaseline   (HTp input);
		static std::string  base40ToTrans   (int base40);
		static int     transToBase40        (const std::string& input);
		static int     base40IntervalToLineOfFifths(int trans);
		static std::string  keyNumberToKern (int number);
      static int     kernKeyToNumber      (const std::string& aKernString);

		static int     base7ToBase40        (int base7);
      static int     base7ToBase12        (int aPitch, int alter = 0);
		static int     base40IntervalToDiatonic(int base40interval);
      static HumNum  kernToDuration       (const std::string& aKernString);


		// **mens, mensual notation, defiend in Convert-mens.cpp
		static bool    isMensRest           (const std::string& mensdata);
		static bool    isMensNote           (const std::string& mensdata);
		static bool    hasLigatureBegin     (const std::string& mensdata);
		static bool    hasRectaLigatureBegin(const std::string& mensdata);
		static bool    hasObliquaLigatureBegin(const std::string& mensdata);
		static bool    hasLigatureEnd       (const std::string& mensdata);
		static bool    hasRectaLigatureEnd  (const std::string& mensdata);
		static bool    hasObliquaLigatureEnd(const std::string& mensdata);
		static bool    getMensStemDirection (const std::string& mensdata);

		static std::string mensToRecip      (char rhythm, bool altera,
		                                     bool perfecta, bool imperfecta,
		                                     int maximodus, int modus,
		                                     int tempus, int prolatio);
		static HumNum  mensToDuration       (char rhythm, bool altera,
		                                     bool perfecta, bool imperfecta,
		                                     int maximodus, int modus,
		                                     int tempus, int prolatio);
		static int metToMensurationLevels   (const std::string& metsig);
		static HumNum mensToDuration        (const std::string& menstok, int rlev);
		static HumNum mensToDuration        (HTp menstok, const std::string& mettok);
		static HumNum mensToDuration        (HTp menstok);

		// older functions to enhance or remove:
		static HumNum  mensToDuration       (const std::string& mensdata, HumNum scale = 4,
		                                     const std::string& separator = " ");
		static std::string  mensToRecip     (const std::string& mensdata, HumNum scale = 4,
		                                     const std::string& separator = " ");
		static HumNum  mensToDurationNoDots (const std::string& mensdata, HumNum scale = 4,
		                                     const std::string& separator = " ");

		// MuseData conversions in Convert-musedata.cpp
      static int         museToBase40                    (const std::string& pitchString);
      static std::string musePitchToKernPitch            (const std::string& museInput);
		static std::string museClefToKernClef              (const std::string& mclef);
		static std::string museKeySigToKernKeySig          (const std::string& mkeysig);
		static std::string museTimeSigToKernTimeSig        (const std::string& mtimesig);
		static std::string museMeterSigToKernMeterSig      (const std::string& mtimesig);
		static std::string museFiguredBassToKernFiguredBass(const std::string& mfb);

		// Harmony processing, defined in Convert-harmony.cpp
		static std::vector<int> minorHScaleBase40(void);
		static std::vector<int> majorScaleBase40 (void);
		static int              keyToInversion   (const std::string& harm);
		static int              keyToBase40      (const std::string& key);
		static std::vector<int> harmToBase40     (HTp harm, const std::string& key) {
		                                          return harmToBase40(*harm, key); }
		static std::vector<int> harmToBase40     (HTp harm, HTp key) {
		                                          return harmToBase40(*harm, *key); }
		static std::vector<int> harmToBase40     (const std::string& harm, const std::string& key);
		static std::vector<int> harmToBase40     (const std::string& harm, int keyroot, int keymode);
		static void             makeAdjustedKeyRootAndMode(const std::string& secondary,
		                                          int& keyroot, int& keymode);
		static int              chromaticAlteration(const std::string& content);

		// data-type specific (other than pitch/rhythm),
		// defined in Convert-kern.cpp
		static bool isKernRest              (const std::string& kerndata);
		static bool isKernNote              (const std::string& kerndata);
		static bool isKernNoteAttack        (const std::string& kerndata);
		static bool hasKernSlurStart        (const std::string& kerndata);
		static bool hasKernSlurEnd          (const std::string& kerndata);
		static bool hasKernPhraseStart      (const std::string& kerndata);
		static bool hasKernPhraseEnd        (const std::string& kerndata);
		static char hasKernStemDirection    (const std::string& kerndata);
		static bool isKernSecondaryTiedNote (const std::string& kerndata);
		static std::string getKernPitchAttributes(const std::string& kerndata);
		static HumNum kernTimeSignatureBottomToDuration (const std::string& aKernString);
		static int kernTimeSignatureTop (const std::string& aKernString);

		static int  getKernSlurStartElisionLevel  (const std::string& kerndata, int index);
		static int  getKernSlurEndElisionLevel    (const std::string& kerndata, int index);
		static int  getKernPhraseStartElisionLevel(const std::string& kerndata, int index);
		static int  getKernPhraseEndElisionLevel  (const std::string& kerndata, int index);
		static int  getKernBeamStartElisionLevel  (const std::string& kerndata, int index);
		static int  getKernBeamEndElisionLevel    (const std::string& kerndata, int index);

		// String processing, defined in Convert-string.cpp
		static std::vector<std::string> splitString   (const std::string& data,
		                                               char separator = ' ');
		static void    replaceOccurrences        (std::string& source,
		                                          const std::string& search,
		                                          const std::string& replace);
		static std::string  repeatString         (const std::string& pattern, int count);
		static std::string  encodeXml            (const std::string& input);
		static std::string  getHumNumAttributes  (const HumNum& num);
		static std::string  trimWhiteSpace       (const std::string& input);
		static std::string  generateRandomId     (int length);
		static bool    startsWith                (const std::string& input,
		                                          const std::string& searchstring);
		static bool    contains(const std::string& input, const std::string& pattern);
		static bool    contains(const std::string& input, char pattern);
		static bool    contains(std::string* input, const std::string& pattern);
		static bool    contains(std::string* input, char pattern);
		static void    makeBooleanTrackList      (std::vector<bool>& spinelist,
		                                          const std::string& spinestring,
		                                          int maxtrack);
		static std::vector<int> extractIntegerList(const std::string& input, int maximum);
		// private functions for extractIntegerList:
		static void processSegmentEntry(std::vector<int>& field, const std::string& astring, int maximum);
		static void removeDollarsFromString(std::string& buffer, int maximum);

		// Mathematical processing, defined in Convert-math.cpp
		static int     getLcm               (const std::vector<int>& numbers);
		static int     getGcd               (int a, int b);
		static void    primeFactors         (std::vector<int>& output, int n);
		static double  nearIntQuantize      (double value,
		                                    double delta = 0.00001);
		static double  significantDigits    (double value, int digits);
		static bool    isNaN                (double value);
		static bool    isPowerOfTwo         (int value);
		static double  pearsonCorrelation   (const std::vector<double> &x, const std::vector<double> &y);
		static double  standardDeviation    (const std::vector<double>& x);
		static double  standardDeviation    (const std::vector<int>& x);
		static double  standardDeviationSample(const std::vector<double>& x);
		static double  standardDeviationSample(const std::vector<int>& x);
		static double  mean                 (const std::vector<double>& x);
		static double  mean                 (const std::vector<int>& x);
		static int     romanNumeralToInteger(const std::string& roman);
		static double  coefficientOfVariationSample(const std::vector<double>& x);
		static double  coefficientOfVariationPopulation(const std::vector<double>& x);
		static double  nPvi                 (const std::vector<double>& x);

		// instrument related functions defined in Convert-instrument.cpp
		static std::vector<std::pair<std::string, std::string>> getInstrumentList(void);

		// Reference record functions defined in Convert-reference.cpp
		static std::string getReferenceKeyMeaning(HTp token);
		static std::string getReferenceKeyMeaning(const std::string& token);
		static std::string getLanguageName(const std::string& abbreviation);
};



class PixelColor {
	public:
		             PixelColor     (void);
		             PixelColor     (const std::string& color);
		             PixelColor     (const PixelColor& color);
		             PixelColor     (int red, int green, int blue);
		             PixelColor     (float red, float green, float blue);
		             PixelColor     (double red, double green, double blue);
		            ~PixelColor     ();

		void         invert         (void);
		PixelColor&  setColor       (const std::string& colorstring);
		PixelColor&  setColor       (int red, int green, int blue);
		int          getRed         (void);
		int          getGreen       (void);
		int          getBlue        (void);
		void         setRed         (int value);
		void         setGreen       (int value);
		void         setBlue        (int value);
		float        getRedF        (void);
		float        getGreenF      (void);
		float        getBlueF       (void);
		void         setRedF        (float value);
		void         setGreenF      (float value);
		void         setBlueF       (float value);
		void         setColor       (PixelColor& color);
		PixelColor&  setHue         (float value);
		PixelColor&  setTriHue      (float value);
		PixelColor&  makeGrey       (void);
		PixelColor&  makeGray       (void);
		PixelColor&  setGrayNormalized(double value);
		PixelColor&  setGreyNormalized(double value);
		int          operator>      (int number);
		int          operator<      (int number);
		int          operator==     (PixelColor& color);
		int          operator!=     (PixelColor& color);
		PixelColor&  operator=      (PixelColor color);
		PixelColor&  operator=      (int value);
		PixelColor   operator+      (PixelColor& color);
		PixelColor&  operator+=     (int number);
		PixelColor   operator-      (PixelColor& color);
		PixelColor&  operator*=     (double number);
		PixelColor   operator*      (PixelColor& color);
		PixelColor   operator*      (double color);
		PixelColor   operator*      (int color);
		PixelColor   operator/      (double number);
		PixelColor   operator/      (int number);

		PixelColor&  rgb2hsi        (void);
		PixelColor&  hsi2rgb        (void);
		PixelColor   getHsi         (void);
		PixelColor   getRgb         (void);
		std::string  getHexColor    (void);

		PixelColor   getColor       (const std::string& colorstring);
		static PixelColor   mix     (PixelColor& color1, PixelColor& color2);

		void         writePpm6      (std::ostream& out);
		void         writePpm3      (std::ostream& out);

	public:
		unsigned char   Red;
		unsigned char   Green;
		unsigned char   Blue;
		// maybe add opacity byte or option byte to fill out 4 byte space.

	private:
		float   charToFloat         (int value);
		int     floatToChar         (float value);
		int     limit               (int value, int min, int max);
};


// for use with P3 ASCII pnm images: print red green blue triplet.
std::ostream& operator<<(std::ostream& out, PixelColor apixel);




class GotScore {

	public:
		struct EventAtTime {
			double timestamp;
			std::vector<std::string> rhythms;
			std::vector<std::string> pitches;
		};

		class Measure {
			public:
				Measure(void) {};
				~Measure() {};
				std::ostream& print(std::ostream& out);

				void printKernBarline(std::ostream& out, bool textQ);
				void printTempoLine(std::ostream& out, const std::string& met, bool textQ);

				// Each rhythm+pitch pairing with computed start time and duration
				class TimedEvent {
					public:
						double timestamp;
						double duration;
						std::string rhythm;
						std::string pitch;
						bool isInterpretation = false;  // true if rhythm starts with '*'
				};

			public:
				// m_parent: A pointer to the GotScore object that the measure belongs to.
				GotScore* m_owner = NULL;

				// m_barnum: The measure number for the measure.
				std::string m_barnum;

				// m_linebreak: The linebreak group to add to end of measure
				// when converting to **got or **kern  There are two labels:
				//    half = linebreak at the half-system at the binding between
				//           physical pages (each system takes up two pages width).
				//    original = linebreak at the end of a system.
				//    and empty m_linebreak means that there are no breaks after
				//    this measure.
				// To encode half breaks, add the letter "p" to the end of the 
				// current measure number.  This will be removed from the text of
				// m_barline, and the "p" will convert to "half" in m_linebreak.
				// The end of the system will be inferred from the system number in
				// the GOT TSV data.
				std::string m_linebreak;

				// m_text: the text content for the measure.
				std::string m_text;

				// m_error: Any parsing error message when converting to **kern
				std::vector<std::string> m_error;

				// m_rhythms: First dimension is voice (highest to lowest)
				// Second dimension is rhythm "word" first to last in measure
				std::vector<std::vector<std::string>> m_rhythms;

				// m_pitches: First dimension is voice (highest to lowest)
				// Second dimension is pitch "word" first to last in measure
				std::vector<std::vector<std::string>> m_pitches;

				// m_splitRhythms: First dimension is voice (highest to lowest)
				// Second dimension is rhythm "word" first to last in measure
				// Third dimension is rhythm "token" first to last in word
				std::vector<std::vector<std::vector<std::string>>> m_splitRhythms;

				// m_splitPitches: First dimension is voice (highest to lowest)
				// Second dimension is pitch "word" first to last in measure
				// Third dimension is pitch "token" first to last in word
				std::vector<std::vector<std::vector<std::string>>> m_splitPitches;

				// m_kerns: First dimension is the voice (highest to lowest),
				// second dimension is flattening of the 2nd and 3rd dimensions
				// of m_splitPitches.
				std::vector<std::vector<std::string*>> m_kerns;

				// m_diatonic: linearized pitch by voice for marking editorial accidentals.
				std::vector<std::vector<int>> m_diatonic;

				// m_accid: chromatic alterations of m_diatonic pitches.
				std::vector<std::vector<int>> m_accid;

				// m_accidState: The diatonic accidental state at the end of the
				// measure.  This is used to create editorial accidentals and 
				// cautionary natural accidentals.  First dimension is voice number,
				// second dimension is CDEFGAB accidental states, 0 = natural 1=sharp, -1=flat.
				std::vector<std::vector<int>> m_accidState;

				// m_voiceEvents: events per voice
				std::vector<std::vector<TimedEvent>> m_voiceEvents;

		};

	public:
		         GotScore        (void);
		         GotScore        (std::stringstream& ss);
		         GotScore        (const std::string& s);
		        ~GotScore        ();

		void     loadLines       (std::stringstream& ss);
		void     loadLines       (const std::string& s);
		bool     prepareMeasures (std::ostream& out);
		void     clear           (void);

		std::ostream& printInputFile  (std::ostream& out);
		std::ostream& printCells      (std::ostream& out);
		std::ostream& printMeasures   (std::ostream& out);

		std::string getGotHumdrum         (void);
		std::string getGotHumdrumMeasure  (GotScore::Measure& mdata);

		std::string getKernHumdrum        (void);
		std::string getKernHumdrumMeasure (GotScore::Measure& mdata);

		void        processUnderscoreTies(std::vector<std::string*>& pitches);
		void        processRhythmTies(std::vector<std::string*>& rhythms, std::vector<std::string*>& pitches);
		std::string mergeRhythmAndPitchIntoNote(const std::string& r, const std::string& p);

		std::string getHeaderInfo(int index);
		std::string getFooterInfo(void);
		void        getDiatonicAccid(const std::string& pitch, int& d, int& a);
		void        prepareAccidentals(void);
		void        markEditorialAccidentals(GotScore::Measure& measure, int voice);
		void        checkForCautionaryAccidentals(int mindex, int vindex);
		void        cleanRhythmValues(std::vector<std::vector<std::string>>& rhythms);

		void        setNoEditorial(void);
		void        setCautionary(void);
		void        setNoForcedAccidentals(void);

	protected:
		void     parse                    (void);
		void     prepareCells             (void);
		bool     processSystemMeasures    (int barIndex, int system, std::ostream& out);
		void     splitMeasureTokens       (void);
		void     splitMeasureTokens       (GotScore::Measure& mdata);
		void     pairLeadingDots          (void);
		void     processDotsForMeasure    (GotScore::Measure& mdata);
		void     processPitchDotsByVoice  (std::vector<std::string*>& pitches);
		void     processDotTiedNotes      (void);
		void     buildVoiceEvents         (void);
		double   durationFromRhythmToken  (const std::string& token);
		std::vector<GotScore::EventAtTime> alignEventsByTimestamp(const GotScore::Measure& mdata);
		std::vector<std::string> convertGotToKernPitches (std::vector<std::string>& gotpitch);
		std::string convertGotToKernPitch (const std::string& gotpitch);
		void     storePitchHistograms     (std::vector<std::vector<std::string*>>& P);
		std::vector<std::string> generateVoiceClefs(void);
		std::string chooseClef(double mean, double min, double max);
		void     trimSpaces(std::string& s);

		static int kernToBase40PC       (const std::string& kerndata);
		static int kernToAccidentalCount(const std::string& kerndata);
		static int kernToBase12PC       (const std::string& kerndata);
		static int kernToOctaveNumber   (const std::string& kerndata);
		static int kernToMidiNoteNumber (const std::string& kerndata);
		static int kernToDiatonicPC     (const std::string& kerndata);

		std::vector<std::string> tokenizeRhythmString (const std::string& input);
		std::vector<std::string> tokenizePitchString  (const std::string& input);
		std::vector<std::string> splitBySpaces        (const std::string& input);

	private:
		// m_voices == number of voices in score
		int m_voices = 0;

		// m_pitch_hist == used to calculate the clef for each voice.
		std::vector<std::vector<int>> m_pitch_hist;

		// m_textQ == true if input data has lyric text.
		bool m_textQ = false;

		// m_lines == input text lines, with whitespace removed from ends of lines.
		std::vector<std::string> m_lines;

		// m_cells == m_lines split by tab characters (i.e., TSV data):
		std::vector<std::vector<std::string>> m_cells;

		// m_measures == data organized by measure.
		std::vector<GotScore::Measure> m_measures;

		// m_debugQ == for printing debug statements
		bool m_debugQ = false;

		// m_error == for reporting errors.
		std::stringstream m_error;

		// m_got == for storing **got conversion.
		std::string m_got;

		// m_cautionary == add !!!RDF**kern: i = editorial accidental, paren
		bool m_cautionary;

		// m_kern == for storing **kern conversion.
		std::string m_kern;

		// conversion options:
		bool m_no_editorialQ = false;
		bool m_cautionaryQ   = false;
		bool m_modern_accQ   = false;

};



// SliceType is a list of various Humdrum line types.  Groupings are
// segmented by categories which are prefixed with an underscore.
// For example Notes are in the _Duration group, since they have
// non-zero durations.  Notes and Gracenotes are in the _Data group.
// The indentation shows the various types of groups.
//

enum class SliceType {
				Notes = 1,
			_Duration,
				GraceNotes,
		_Data,
			Measures,
		_Measure,
				Stria,
				Clefs,
				Transpositions,
				KeyDesignations,
				KeySigs,
				TimeSigs,
				MeterSigs,
				Tempos,
				Labels,
				LabelAbbrs,
				Ottavas,
			_RegularInterpretation,
				Exclusives,
				Terminators,
				Manipulators,
			_Manipulator,
		_Interpretation,
			Layouts,
			LocalComments,
	_Spined,
		GlobalComments,
		GlobalLayouts,
		ReferenceRecords,
	_Other,
		Invalid
};


// MeasureType is a list of the style types for a measure (ending type for now)

enum class MeasureStyle {
	Invisible,
	Plain,
	RepeatBackward,
	RepeatForward,
	RepeatBoth,
	Double,
	Final
};



class MxmlMeasure;
class MxmlEvent;

class MxmlPart {
	public:
		              MxmlPart             (void);
		             ~MxmlPart             ();
		void          clear                (void);
		void          enableStems          (void);
		bool          readPart             (const string& id, xml_node partdef,
		                                    xml_node part);
		bool          addMeasure           (xml_node mel);
		bool          addMeasure           (xpath_node mel);
		int           getMeasureCount      (void) const;
		MxmlMeasure*  getMeasure           (int index) const;
		long          getQTicks            (void) const;
		int           setQTicks            (long value);
	   MxmlMeasure*  getPreviousMeasure   (MxmlMeasure* measure) const;
		HumNum        getDuration          (void) const;
		void          allocateSortedEvents (void);
		void          setPartNumber        (int number);
		int           getPartNumber        (void) const;
		int           getPartIndex         (void) const;
		int           getStaffCount        (void) const;
		int           getVerseCount        (void) const;
		int           getVerseCount        (int staffindex) const;
		string        getCaesura           (void) const;
		int           getHarmonyCount      (void) const;
		void          trackStaffVoices     (int staffnum, int voicenum);
		void          printStaffVoiceInfo  (void);
		void          prepareVoiceMapping  (void);
		int           getVoiceIndex        (int voicenum);
		int           getStaffIndex        (int voicenum);
		bool          hasEditorialAccidental(void) const;
		bool          hasDynamics          (void) const;
		bool          hasFiguredBass       (void) const;
		void          parsePartInfo        (xml_node partdeclaration);
		string        getPartName          (void) const;
		string        getPartAbbr          (void) const;
		string        cleanSpaces          (const string& input);
		bool          hasOrnaments         (void) const;

		vector<pair<int, int>> getVoiceMapping (void) { return m_voicemapping; };
		vector<vector<int>> getStaffVoiceHist (void) { return m_staffvoicehist; };


	private:
		void          receiveStaffNumberFromChild (int staffnum, int voicenum);
		void          receiveVerseCount           (int count);
		void          receiveVerseCount           (int staffnum, int count);
		void          receiveHarmonyCount         (int count);
		void          receiveEditorialAccidental  (void);
		void          receiveDynamic              (void);
		void          receiveFiguredBass          (void);
		void          receiveCaesura              (const string& letter);
		void          receiveOrnament             (void);

	protected:
		vector<MxmlMeasure*> m_measures;
		vector<long>         m_qtick;
		int                  m_partnum;
		int                  m_maxstaff;
		vector<int>          m_verseCount;
		int                  m_harmonyCount;
		bool                 m_editorialAccidental;
		bool                 m_stems = false;
		bool                 m_has_dynamics = false;
		bool                 m_has_figured_bass = false;
		string               m_partname;
		string               m_partabbr;
		string               m_caesura;
		bool                 m_hasOrnaments = false;

		// m_staffvoicehist: counts of staff and voice numbers.
		// staff=0 is used for items such as measures.
		// voice=0 is used for nonduration items such as harmony.
		vector<vector<int> > m_staffvoicehist;
	 	vector<pair<int, int> > m_voicemapping; // voicenum -> (staff, voiceindex)

	friend MxmlMeasure;
	friend MxmlEvent;

};



class GridSide {
	public:
		GridSide(void);
		~GridSide();

		int   getVerseCount     (void);
		HTp   getVerse          (int index);
		void  setVerse          (int index, HTp token);
		void  setVerse          (int index, const std::string& token);

		int   getXmlidCount     (void);
		void  setXmlid          (HTp token);
		void  setXmlid          (const std::string& token);
		void  detachXmlid       (void);
		HTp   getXmlid          (void);

		int   getHarmonyCount   (void);
		void  setHarmony        (HTp token);
		void  setHarmony        (const std::string& token);
		void  detachHarmony     (void);
		HTp   getHarmony        (void);

		int   getDynamicsCount  (void);
		void  setDynamics       (HTp token);
		void  setDynamics       (const std::string& token);
		void  detachDynamics    (void);
		HTp   getDynamics       (void);

		int   getFiguredBassCount (void);
		void  setFiguredBass      (HTp token);
		void  setFiguredBass      (const std::string& token);
		void  detachFiguredBass   (void);
		HTp   getFiguredBass      (void);

	private:
		HumdrumToken* m_xmlid        = NULL;
		std::vector<HumdrumToken*> m_verses;
		HumdrumToken* m_dynamics     = NULL;
		HumdrumToken* m_figured_bass = NULL;
		HumdrumToken* m_harmony      = NULL;
};

std::ostream& operator<<(std::ostream& output, GridSide* side);


class GridStaff : public std::vector<GridVoice*>, public GridSide {
	public:
		GridStaff(void);
		~GridStaff();
		GridVoice* setTokenLayer (int layerindex, HTp token, HumNum duration);
		void setNullTokenLayer   (int layerindex, SliceType type, HumNum nextdur);
		void appendTokenLayer    (int layerindex, HTp token, HumNum duration,
		                          const std::string& spacer = " ");
		int getMaxVerseCount     (void);
		string getString         (void);
};

std::ostream& operator<<(std::ostream& output, GridStaff* staff);



class GridPart : public std::vector<GridStaff*>, public GridSide {
	public:
		GridPart(void);
		~GridPart();

	private:
		std::string m_partName;


};

std::ostream& operator<<(std::ostream& output, GridPart* part);
std::ostream& operator<<(std::ostream& output, GridPart& part);



class GridSlice;
class HumGrid;

class GridMeasure : public std::list<GridSlice*> {
	public:
		GridMeasure(HumGrid* owner);
		~GridMeasure();

		GridSlice*   addTempoToken  (const std::string& tok, HumNum timestamp,
		                             int part, int staff, int voice, int maxstaff);
		GridSlice*   addTempoToken  (GridSlice* slice, int partindex,
		                             const std::string& tempo);
		GridSlice*   addTimeSigToken(const std::string& tok, HumNum timestamp,
		                             int part, int staff, int voice, int maxstaff);
		GridSlice*   addMeterSigToken(const std::string& tok, HumNum timestamp,
		                             int part, int staff, int voice, int maxstaff);
		GridSlice*   addKeySigToken (const std::string& tok, HumNum timestamp,
		                             int part, int staff, int voice, int maxstaff);
		GridSlice*   addClefToken   (const std::string& tok, HumNum timestamp,
		                             int part, int staff, int voice, int maxstaff);
		GridSlice*   addBarlineToken(const std::string& tok, HumNum timestamp,
		                             int part, int staff, int voice, int maxstaff);
		GridSlice*   addTransposeToken(const std::string& tok, HumNum timestamp,
		                             int part, int staff, int voice, int maxstaff);
		GridSlice*   addLabelToken  (const std::string& tok, HumNum timestamp,
		                             int part, int staff, int voice, int maxpart,
		                             int maxstaff);
		GridSlice*   addLabelAbbrToken(const std::string& tok, HumNum timestamp,
		                             int part, int staff, int voice, int maxpart,
		                             int maxstaff);
		GridSlice*   addDataToken   (const std::string& tok, HumNum timestamp,
		                             int part, int staff, int voice, int maxstaff);
		GridSlice*   addDataSubtoken(const std::string& tok, HumNum timestamp,
		                             int part, int staff, int voice);
		GridSlice*   addGraceToken  (const std::string& tok, HumNum timestamp,
		                             int part, int staff, int voice, int maxstaff,
		                             int gracenumber);
		GridSlice*   addGlobalLayout(const std::string& tok, HumNum timestamp);
		GridSlice*   addGlobalComment(const std::string& tok, HumNum timestamp);
		GridSlice*   appendGlobalLayout(const std::string& tok, HumNum timestamp);
		bool         transferTokens (HumdrumFile& outfile, bool recip,
		                             bool addbar, int startbarnum = 0);
		HumGrid*     getOwner       (void);
		void         setOwner       (HumGrid* owner);
		HumNum       getDuration    (void);
		void         setDuration    (HumNum duration);
		HumNum       getTimestamp   (void);
		void         setTimestamp   (HumNum timestamp);
		HumNum       getTimeSigDur  (void);
		void         setTimeSigDur  (HumNum duration);
		MeasureStyle getStyle       (void) { return m_style; }
		MeasureStyle getBarStyle    (void) { return getStyle(); }
		void         setStyle       (MeasureStyle style) { m_style = style; }
		void         setBarStyle    (MeasureStyle style) { setStyle(style); }
		void         setKernBar     (const std::string& tok);
		void         setInvisibleBarline(void) { setStyle(MeasureStyle::Invisible); }
		void         setFinalBarlineStyle(void) { setStyle(MeasureStyle::Final); }
		void         setRepeatEndStyle(void) { setStyle(MeasureStyle::RepeatBackward); }
		void         setRepeatBackwardStyle(void) { setStyle(MeasureStyle::RepeatBackward); }
		void         setMeasureNumber(int value);
		int          getMeasureNumber(void);

		bool         isDouble(void)
		                  {return m_style == MeasureStyle::Double;}
		bool         isFinal(void)
		                  {return m_style == MeasureStyle::Final;}
		bool         isRepeatBackward(void)
		                  { return m_style == MeasureStyle::RepeatBackward; }
		bool         isInvisibleBarline(void)
		                  { return m_style == MeasureStyle::Invisible; }
		bool         isRepeatForward(void)
		                  { return m_style == MeasureStyle::RepeatForward; }
		bool         isRepeatBoth(void)
		                  { return m_style == MeasureStyle::RepeatBoth; }
		void         addInterpretationBefore(GridSlice* slice, int partindex, int staffindex, int voiceindex, const std::string& interpretation);
		void         addInterpretationAfter(GridSlice* slice, int partindex, int staffindex, int voiceindex, const std::string& interpretation, HumNum timestamp);
		void         addLayoutParameter(GridSlice* slice, int partindex, const std::string& locomment);
		void         addLayoutParameter(HumNum timestamp, int partindex, int staffindex, const std::string& locomment);
		void         addDynamicsLayoutParameters(GridSlice* slice, int partindex, const std::string& locomment);
		void         addFiguredBassLayoutParameters(GridSlice* slice, int partindex, const std::string& locomment);
		GridSlice*   addFiguredBass(HTp token, HumNum timestamp, int part, int maxstaff);
		GridSlice*   addFiguredBass(const std::string& tok, HumNum timestamp, int part, int maxstaff);
		bool         isInvisible(void);
		bool         isSingleChordMeasure(void);
		bool         isMonophonicMeasure(void);
		GridSlice*   getLastSpinedSlice(void);
		GridSlice*   getFirstSpinedSlice(void);

	protected:
		void         appendInitialBarline(HumdrumFile& infile, int startbarnum = 0);

	private:
		HumGrid*     m_owner;
		HumNum       m_duration;
		HumNum       m_timestamp;
		HumNum       m_timesigdur;
		MeasureStyle m_style;
		std::string  m_kernBar;
		int          m_barnum = -1;
};

std::ostream& operator<<(std::ostream& output, GridMeasure& measure);
std::ostream& operator<<(std::ostream& output, GridMeasure* measure);


class HumGrid;


class GridSlice : public std::vector<GridPart*> {
	public:
		GridSlice(GridMeasure* measure, HumNum timestamp, SliceType type,
		          int partcount = 0);
		GridSlice(GridMeasure* measure, HumNum timestamp, SliceType type,
		          const GridSlice& slice);
		GridSlice(GridMeasure* measure, HumNum timestamp, SliceType type,
		          GridSlice* slice);
		~GridSlice();

		bool isNoteSlice(void)          { return m_type == SliceType::Notes;            }
		bool isGraceSlice(void)         { return m_type == SliceType::GraceNotes;       }
		bool isMeasureSlice(void)       { return m_type == SliceType::Measures;         }
		bool isClefSlice(void)          { return m_type == SliceType::Clefs;            }
		bool isLabelSlice(void)         { return m_type == SliceType::Labels;           }
		bool isLabelAbbrSlice(void)     { return m_type == SliceType::LabelAbbrs;       }
		bool isTransposeSlice(void)     { return m_type == SliceType::Transpositions;   }
		bool isKeySigSlice(void)        { return m_type == SliceType::KeySigs;          }
		bool isKeyDesignationSlice(void){ return m_type == SliceType::KeyDesignations;  }
		bool isTimeSigSlice(void)       { return m_type == SliceType::TimeSigs;         }
		bool isTempoSlice(void)         { return m_type == SliceType::Tempos;           }
		bool isMeterSigSlice(void)      { return m_type == SliceType::MeterSigs;        }
		bool isManipulatorSlice(void)   { return m_type == SliceType::Manipulators;     }
		bool isLayoutSlice(void)        { return m_type == SliceType::Layouts;          }
		bool isLocalLayoutSlice(void)   { return m_type == SliceType::Layouts;          }
		bool isInvalidSlice(void)       { return m_type == SliceType::Invalid;          }
		bool isGlobalComment(void)      { return m_type == SliceType::GlobalComments;   }
		bool isGlobalLayout(void)       { return m_type == SliceType::GlobalLayouts;    }
		bool isReferenceRecord(void)    { return m_type == SliceType::ReferenceRecords; }
		bool isOttavaRecord(void)       { return m_type == SliceType::Ottavas;          }
		bool isInterpretationSlice(void);
		bool isDataSlice(void);
		bool hasSpines(void);
		std::string getNullTokenForSlice(void);
		SliceType getType(void)    { return m_type; }

		void transferTokens        (HumdrumFile& outfile, bool recip);
		void initializePartStaves  (std::vector<MxmlPart>& partdata);
		void initializeBySlice     (GridSlice* slice);
		void initializeByStaffCount(int staffcount);
		void reportVerseCount      (int partindex, int staffindex, int count);

		HumNum       getDuration        (void);
		void         setDuration        (HumNum duration);
		HumNum       getTimestamp       (void);
		void         setTimestamp       (HumNum timestamp);
		void         setOwner           (HumGrid* owner);
		HumGrid*     getOwner           (void);
		HumNum       getMeasureDuration (void);
		HumNum       getMeasureTimestamp(void);
		GridMeasure* getMeasure         (void);
		void         invalidate         (void);

		void transferSides        (HumdrumLine& line, GridStaff& sides,
		                           const std::string& empty, int maxxcount,
		                           int maxvcount, int maxhcount, int maxfcount);
		void transferSides        (HumdrumLine& line, GridPart& sides,
		                           int partindex, const std::string& empty,
		                           int maxxcount, int maxvcount, int maxhcount,
		                           int maxdcount, int maxfcount);
		int getVerseCount         (int partindex, int staffindex);
		int getHarmonyCount       (int partindex, int staffindex = -1);
		int getXmlidCount         (int partindex, int staffindex = -1);
		int getDynamicsCount      (int partindex, int staffindex = -1);
		int getFiguredBassCount   (int partindex, int staffindex = -1);
		void addToken             (const std::string& tok, int parti, int staffi, int voicei);

	protected:
		HTp  createRecipTokenFromDuration  (HumNum duration);

	private:
		HumGrid*     m_owner;
		GridMeasure* m_measure;
		HumNum       m_timestamp;
		HumNum       m_duration;
		SliceType    m_type;

};


std::ostream& operator<<(std::ostream& output, GridSlice* slice);
std::ostream& operator<<(std::ostream& output, GridSlice& slice);



class GridVoice {
	public:
		GridVoice(void);
		GridVoice(HTp token, HumNum duration);
		GridVoice(const char* token, HumNum duration);
		GridVoice(const std::string& token, HumNum duration);
		~GridVoice();

		bool   isTransfered       (void);

		HTp    getToken           (void) const;
		void   setToken           (HTp token);
		void   setToken           (const std::string& token);
		void   setToken           (const char* token);
		bool   isNull             (void) const;

		void   setDuration        (HumNum duration);
		HumNum getDuration        (void) const;
		HumNum getDurationToNext  (void) const;
		HumNum getDurationToPrev  (void) const;
		void   setDurationToPrev  (HumNum dur);
		void   incrementDuration  (HumNum duration);
		void   forgetToken        (void);
		std::string getString          (void);

	protected:
		void   setTransfered      (bool state);

	private:
		HTp    m_token;
		HumNum m_nextdur;
		HumNum m_prevdur;
		bool   m_transfered;

	friend class GridSlice;
};

std::ostream& operator<<(std::ostream& output, GridVoice* voice);
std::ostream& operator<<(std::ostream& output, GridVoice& voice);



class HumGrid : public std::vector<GridMeasure*> {
	public:
		HumGrid(void);
		~HumGrid();
		void enableRecipSpine           (void);
		bool transferTokens             (HumdrumFile& outfile, int startbarnum = 0, const string& interp = "**kern");
		int  getHarmonyCount            (int partindex);
		int  getDynamicsCount           (int partindex);
		int  getFiguredBassCount        (int partindex);
		int  getXmlidCount              (int partindex);
		int  getVerseCount              (int partindex, int staffindex);
		bool hasDynamics                (int partindex);
		bool hasXmlids                  (int partindex);
		bool hasFiguredBass             (int partindex);
		void setDynamicsPresent         (int partindex);
		void setXmlidsPresent           (int partindex);
		void setFiguredBassPresent      (int partindex);
		void setHarmonyPresent          (int partindex);
		void setVerseCount              (int partindex, int staffindex, int count);
		void reportVerseCount           (int partindex, int staffindex, int count);
		void reportXmlidCount           (int partindex, int staffindex, int count);
		void setHarmonyCount            (int partindex, int count);
		void removeRedundantClefChanges (void);
		void removeSibeliusIncipit      (void);
		bool hasPickup                  (void);
		GridMeasure*  addMeasureToBack  (void);
		int  getPartCount               (void);
		int  getStaffCount              (int partindex);
		void deleteMeasure              (int index);
		void setPartName                (int index, const string& name);
		std::string getPartName         (int index);
		void addInvisibleRestsInFirstTrack(void);
		void setPartStaffDimensions     (std::vector<std::vector<GridSlice*>>& nextevent,
		                                 GridSlice* startslice);
		void addInvisibleRest           (std::vector<std::vector<GridSlice*>>& nextevent,
		                                 int index, int p, int s);
		void cleanTempos                (void);
		void cleanTempos                (GridSlice* slice);
		void expandLocalCommentLayers   (void);
		bool buildSingleList            (void);

	protected:
		void calculateGridDurations        (void);
		void insertExclusiveInterpretationLine (HumdrumFile& outfile, const string& interp);
		void insertDataTerminationLine     (HumdrumFile& outfile);
		void appendMeasureLine             (HumdrumFile& outfile,
		                                    GridSlice& slice);
		void insertPartIndications         (HumdrumFile& outfile);
		void insertStaffIndications        (HumdrumFile& outfile);
		void insertPartNames               (HumdrumFile& outfile);
		void addNullTokens                 (void);
		void addNullTokensForGraceNotes    (void);
		void addNullTokensForClefChanges   (void);
		void addNullTokensForLayoutComments(void);
		void checkForNullDataHoles         (void);

		void fillInNullTokensForGraceNotes(GridSlice* graceslice, GridSlice* lastnote,
		                                   GridSlice* nextnote);
		void fillInNullTokensForLayoutComments(GridSlice* layoutslice, GridSlice* lastnote,
		                                   GridSlice* nextnote);
		void fillInNullTokensForClefChanges (GridSlice* clefslice,
		                                    GridSlice* lastnote, GridSlice* nextnote);
		void adjustClefChanges             (void);
		void extendDurationToken           (int slicei, int parti,
		                                    int staffi, int voicei);
		GridVoice* getGridVoice(int slicei, int parti, int staffi, int voicei);
		void addMeasureLines               (void);
		void addLastMeasure                (void);
		bool manipulatorCheck              (void);
		GridSlice* manipulatorCheck        (GridSlice* ice1, GridSlice* ice2);
		void cleanupManipulators           (void);
		void cleanManipulator              (std::vector<GridSlice*>& newslices,
		                                    GridSlice* curr);
		GridSlice* checkManipulatorExpand  (GridSlice* curr);
		GridSlice* checkManipulatorContract(GridSlice* curr);
		void transferMerges                (GridStaff* oldstaff,
		                                    GridStaff* oldlaststaff,
		                                    GridStaff* newstaff,
		                                    GridStaff* newlaststaff, int pindex,
		                                    int sindex);
		void transferOtherParts            (GridSlice* oldline, GridSlice* newline, int maxpart);
		void insertExInterpSides           (HLp line, int part, int staff);
		void insertSideTerminals           (HLp line, int part, int staff);
		void insertSidePartInfo            (HLp line, int part, int staff);
		void insertSideStaffInfo           (HLp line, int part, int staff, int staffnum);
		void insertSideNullInterpretations (HLp line, int part, int staff);
		void getMetricBarNumbers           (std::vector<int>& barnums);
		string  createBarToken             (int m, int barnum,
		                                    GridMeasure* measure);
		string getBarStyle                 (GridMeasure* measure);
		void adjustExpansionsInStaff       (GridSlice* newmanip, GridSlice* curr,
		                                    int p, int s);
		void transferNonDataSlices         (GridMeasure* output, GridMeasure* input);
		string extractMelody               (GridMeasure* measure);
		void insertMelodyString            (GridMeasure* measure, const string& melody);
		GridVoice* createVoice             (const string& tok, const string& post, HumNum duration, int pindex, int sindex);
		HTp createHumdrumToken             (const string& tok, int pindex, int sindex);
		GridSlice* getNextSpinedLine       (const GridMeasure::iterator& it, int measureindex);
		void matchVoices                   (GridSlice* current, GridSlice* last);
		void adjustVoices                  (GridSlice* curr, GridSlice* newmanip, int partsplit);
		void createMatchedVoiceCount       (GridStaff* snew, GridStaff* sold, int p, int s);
		void matchLayers                   (GridSlice* output, GridSlice* input);
		void matchLayers                   (GridStaff* output, GridStaff* input);

	private:
		std::vector<GridSlice*>       m_allslices;
		std::vector<std::vector<int>> m_verseCount;
		std::vector<int>              m_harmonyCount;
		bool                          m_pickup;
		std::vector<bool>             m_dynamics;
		std::vector<bool>             m_xmlids;
		std::vector<bool>             m_figured_bass;
		std::vector<bool>             m_harmony;

		std::vector<std::string>      m_partnames;

		// options:
		bool m_recip;               // include **recip spine in output
		bool m_musicxmlbarlines;    // use measure numbers from <measure> element

};

ostream& operator<<(ostream& out, HumGrid& grid);



class MxmlMeasure;
class MxmlPart;

// Event types: These are all of the XML elements which can be children of
// the measure element in MusicXML.

enum measure_event_type {
	mevent_unknown,
	mevent_attributes,
	mevent_backup,
	mevent_barline,
	mevent_bookmark,
	mevent_direction,
	mevent_figured_bass,
	mevent_forward,
	mevent_grouping,
	mevent_harmony,
	mevent_link,
	mevent_note,
	mevent_print,
	mevent_sound,
	mevent_float       // category for GridSides not attached to note onsets
};


class MxmlEvent {
	public:
		                   MxmlEvent          (MxmlMeasure* measure);
		                  ~MxmlEvent          ();
		void               clear              (void);
		void               enableStems        (void);
		bool               parseEvent         (xml_node el, xml_node nextel,
		                                       HumNum starttime);
		bool               parseEvent         (xpath_node el, HumNum starttime);
		void               setTickStart       (long value, long ticks);
		void               setTickDur         (long value, long ticks);
		void               setStartTime       (HumNum value);
		void               setDuration        (HumNum value);
		void               setDurationByTicks (long value, xml_node el = xml_node(NULL));
		void               setModification    (HumNum value);
		HumNum             getStartTime       (void) const;
		HumNum             getDuration        (void) const;
		HumNum             getModification    (void) const;
		void               setOwner           (MxmlMeasure* measure);
		MxmlMeasure*       getOwner           (void) const;
		const char*        getName            (void) const;
		int                setQTicks          (long value);
		long               getQTicks          (void) const;
		long               getIntValue        (const char* query) const;
		bool               hasChild           (const char* query) const;
		void               link               (MxmlEvent* event);
		bool               isLinked           (void) const;
		bool               isRest             (void);
		bool               isGrace            (void);
		bool               hasGraceSlash      (void);
		bool               isFloating         (void);
		int                hasSlurStart       (std::vector<int>& directions);
		int                hasSlurStop        (void);
		void               setLinked          (void);
		std::vector<MxmlEvent*> getLinkedNotes     (void);
		void               attachToLastEvent  (void);
		bool               isChord            (void) const;
		std::ostream&      print              (std::ostream& out);
		int                getSequenceNumber  (void) const;
		int                getVoiceNumber     (void) const;
		void               setVoiceNumber     (int value);
		int                getStaffNumber     (void) const;
		int                getStaffIndex      (void) const;
		int                getCrossStaffOffset(void) const;
		int                getVoiceIndex      (int maxvoice = 4) const;
		void               setStaffNumber     (int value);
		measure_event_type getType            (void) const;
		int                getPartNumber      (void) const;
		int                getPartIndex       (void) const;
		std::string        getRecip           (void) const;
		std::string        getKernPitch       (void);
		std::string        getPrefixNoteInfo  (void) const;
		std::string        getPostfixNoteInfo (bool primarynote, const std::string& recip) const;
		xml_node           getNode            (void);
		xml_node           getHNode           (void);
		HumNum             getTimeSigDur      (void);
		std::string        getElementName     (void);
		void               addNotations       (std::stringstream& ss,
		                                       xml_node notations,
		                                       int beamstarts,
		                                       const std::string& recip) const;
		void               reportVerseCountToOwner    (int count);
		void               reportVerseCountToOwner    (int staffnum, int count);
		void               reportHarmonyCountToOwner  (int count);
		void               reportMeasureStyleToOwner  (MeasureStyle style);
		void               reportEditorialAccidentalToOwner(void);
		void               reportDynamicToOwner       (void);
		void               reportFiguredBassToOwner   (void);
		void               reportCaesuraToOwner       (const std::string& letter = "Z") const;
		void               reportOrnamentToOwner      (void) const;
      void               makeDummyRest      (MxmlMeasure* owner,
		                                       HumNum startime,
		                                       HumNum duration,
		                                       int staffindex = 0,
		                                       int voiceindex = 0);
		void               setVoiceIndex      (int voiceindex);
		void               forceInvisible     (void);
		bool               isInvisible        (void);
		void               setBarlineStyle    (xml_node node);
		void               setTexts           (std::vector<std::pair<int, xml_node>>& nodes);
		void               setTempos          (std::vector<std::pair<int, xml_node>>& nodes);
		std::vector<std::pair<int, xml_node>>&  getTexts           (void);
		std::vector<std::pair<int, xml_node>>&  getTempos          (void);
		void               setDynamics        (xml_node node);
		void               setBracket         (xml_node node);
		void               setHairpinEnding   (xml_node node);
		void               addFiguredBass     (xml_node node);
		std::vector<xml_node> getDynamics     (void);
		std::vector<xml_node> getBrackets     (void);
		xml_node           getHairpinEnding   (void);
		int                getFiguredBassCount(void);
		xml_node           getFiguredBass     (int index);
		std::string        getRestPitch       (void) const;

	protected:
		HumNum             m_starttime;    // start time in quarter notes of event
		HumNum             m_duration;     // duration in quarter notes of event
      HumNum             m_modification; // tuplet time adjustment of note
		measure_event_type m_eventtype;    // enumeration type of event
		xml_node           m_node;         // pointer to event in XML structure
		MxmlMeasure*       m_owner;        // measure that contains this event
		std::vector<MxmlEvent*> m_links;   // list of secondary chord notes
		bool               m_linked;       // true if a secondary chord note
		int                m_sequence;     // ordering of event in XML file
		static int         m_counter;      // counter for sequence variable
		short              m_staff;        // staff number in part for event
		short              m_voice;        // voice number in part for event
		int                m_voiceindex;   // voice index of item (remapping)
      int                m_maxstaff;     // maximum staff number for measure
		xml_node           m_hnode;        // harmony label starting at note event
		bool               m_invisible;    // for forceInvisible();
		bool               m_stems;        // for preserving stems

		std::vector<xml_node> m_dynamics;   // dynamics <direction> starting just before note
		xml_node          m_hairpin_ending; // hairpin <direction> starting just after note and before new measure
		std::vector<xml_node>  m_figured_bass; // fb starting just before note
		std::vector<xml_node>  m_brackets;  // brackets to start/end before/after note
		std::vector<std::pair<int, xml_node>>  m_text;   // text <direction> starting just before note
		std::vector<std::pair<int, xml_node>>  m_tempo;   // tempo starting just before note

	private:
   	void   reportStaffNumberToOwner  (int staffnum, int voicenum);
		void   reportTimeSigDurToOwner   (HumNum duration);
		int    getDotCount               (void) const;

	public:
		static HumNum getQuarterDurationFromType (const char* type);
		static bool   nodeType             (xml_node node, const char* testname);
		static HumNum getEmbeddedDuration  (HumNum& modification, xml_node el = xml_node(NULL));


	friend MxmlMeasure;
	friend MxmlPart;
};


std::ostream& operator<<(std::ostream& output, xml_node element);



class MxmlEvent;
class MxmlPart;


class SimultaneousEvents {
	public:
		SimultaneousEvents(void) { }
		~SimultaneousEvents() { }
		HumNum starttime;              // start time of events
		HumNum duration;               // duration to next non-zero duration
		vector<MxmlEvent*> zerodur;    // zero-duration elements at this time
		vector<MxmlEvent*> nonzerodur; // non-zero dur elements at this time
};


class MxmlMeasure {
	public:
		              MxmlMeasure        (MxmlPart* part);
		             ~MxmlMeasure        (void);
		void          clear              (void);
		void          enableStems        (void);
		bool          parseMeasure       (xml_node mel);
		bool          parseMeasure       (xpath_node mel);
		void          setStartTimeOfMeasure (HumNum value);
		void          setStartTimeOfMeasure (void);
		void          setDuration        (HumNum value);
		HumNum        getStartTime       (void) const;
		HumNum        getTimestamp       (void) const { return getStartTime(); }
		HumNum        getDuration        (void) const;
		void          setOwner           (MxmlPart* part);
		MxmlPart*     getOwner           (void) const;
		int           getPartNumber      (void) const;
		int           getPartIndex       (void) const;
		int           setQTicks          (long value);
		long          getQTicks          (void) const;
		void          attachLastEventToPrevious  (void);
		void          calculateDuration  (void);
		int           getEventCount      (void) const;
		vector<SimultaneousEvents>* getSortedEvents(void);
		MxmlEvent*    getEvent           (int index) const;

		void          setNextMeasure     (MxmlMeasure* event);
		MxmlMeasure*  getNextMeasure     (void) const;
		MxmlMeasure*  getPreviousMeasure (void) const;
		void          setPreviousMeasure (MxmlMeasure* event);

		int           getVoiceIndex      (int voicenum);
		int           getStaffIndex      (int voicenum);
		void          setTimeSigDur      (HumNum duration);
		HumNum        getTimeSigDur      (void);
		void          addDummyRest       (void);
		void          addDummyRest       (HumNum starttime, HumNum duration,
		                                  int staffindex, int voiceindex);
		vector<MxmlEvent*>& getEventList (void);
		void  sortEvents                 (void);
		void  forceLastInvisible         (void);
		MeasureStyle  getStyle           (void);
		MeasureStyle  getBarStyle        (void);
		void  setStyle                   (MeasureStyle style);
		void  setBarStyle                (MeasureStyle style);
		void  makeFinalBarline(void)   { m_style = MeasureStyle::Final; }
		bool  isFinal(void)            { return m_style == MeasureStyle::Final; }
		bool  isDouble(void)           { return m_style == MeasureStyle::Double; }
		bool  isRepeatBackward(void)   { return m_style == MeasureStyle::RepeatBackward; }
		bool  isRepeatForward(void)    { return m_style == MeasureStyle::RepeatForward; }
		bool  isRepeatBoth(void)       { return m_style == MeasureStyle::RepeatBoth; }

	private:
		void  receiveStaffNumberFromChild         (int staffnum, int voicenum);
		void  receiveTimeSigDurFromChild          (HumNum duration);
		void  receiveMeasureStyleFromChild        (MeasureStyle style);
		void  receiveEditorialAccidentalFromChild (void);
		void  receiveOrnamentFromChild            (void);
   	void  reportStaffNumberToOwner            (int staffnum, int voicenum);
		void  reportVerseCountToOwner             (int count);
		void  reportVerseCountToOwner             (int staffindex, int count);
		void  reportHarmonyCountToOwner           (int count);
		void  reportEditorialAccidentalToOwner    (void);
		void  reportDynamicToOwner                (void);
		void  reportFiguredBassToOwner            (void);
		void  reportCaesuraToOwner                (const string& letter);
		void  reportOrnamentToOwner               (void);

	protected:
		HumNum             m_starttime; // start time of measure in quarter notes
		HumNum             m_duration;  // duration of measure in quarter notes
		HumNum             m_timesigdur; // duration of measure according to
													// prevailing time signature.
		MxmlPart*          m_owner;     // part which contains measure
		MxmlMeasure*       m_previous;  // previous measure in part or null
		MxmlMeasure*       m_following; // following measure in part or null
		vector<MxmlEvent*> m_events;    // list of semi-ordered events in measure
		vector<SimultaneousEvents> m_sortedevents; // list of time-sorted events
		MeasureStyle       m_style;     // measure style type
		bool               m_stems = false;

	friend MxmlEvent;
	friend MxmlPart;
};



class Option_register {
	public:
		                 Option_register (void);
		                 Option_register (const std::string& aDefinition, char aType,
		                                  const std::string& aDefaultOption);
		                 Option_register (const std::string& aDefinition, char aType,
		                                  const std::string& aDefaultOption,
		                                  const std::string& aModifiedOption);
		                 Option_register (const Option_register& reg);
		                ~Option_register ();

		Option_register& operator=       (const Option_register& reg);
		void             clearModified   (void);
		std::string      getDefinition   (void);
		std::string      getDefault      (void);
		std::string      getOption       (void);
		std::string      getModified     (void);
		std::string      getDescription  (void);
		bool             isModified      (void);
		char             getType         (void);
		void             reset           (void);
		void             setDefault      (const std::string& aString);
		void             setDefinition   (const std::string& aString);
		void             setDescription  (const std::string& aString);
		void             setModified     (const std::string& aString);
		void             setType         (char aType);
		std::ostream&    print           (std::ostream& out);

	protected:
		std::string      m_definition;
		std::string      m_description;
		std::string      m_defaultOption;
		std::string      m_modifiedOption;
		bool             m_modifiedQ;
		char             m_type;
};


class Options {
	public:
		                Options           (void);
		                Options           (int argc, char** argv);
		                Options           (const Options& options);
		               ~Options           ();

		Options&        operator=         (const Options& options);
		int             argc              (void) const;
		const std::vector<std::string>& argv (void) const;
		int             define            (const std::string& aDefinition);
		int             define            (const std::string& aDefinition,
		                                   const std::string& description);
		std::string     getArg            (int index);
		std::string     getArgument       (int index);
		int             getArgCount       (void);
		int             getArgumentCount  (void);
		std::vector<std::string>& getArgList        (std::vector<std::string>& output);
		std::vector<std::string>& getArgumentList   (std::vector<std::string>& output);
		bool            getBoolean        (const std::string& optionName);
		std::string     getCommand        (void);
		std::string     getCommandLine    (void);
		std::string     getDefinition     (const std::string& optionName);
		double          getDouble         (const std::string& optionName);
		char            getFlag           (void);
		char            getChar           (const std::string& optionName);
		float           getFloat          (const std::string& optionName);
		int             getInt            (const std::string& optionName);
		int             getInteger        (const std::string& optionName);
		std::string     getString         (const std::string& optionName);
		char            getType           (const std::string& optionName);
		int             optionsArg        (void);
		std::ostream&   print             (std::ostream& out);
		std::ostream&   printEmscripten   (std::ostream& out);
		std::ostream&   printOptionList   (std::ostream& out);
		std::ostream&   printOptionListBooleanState(std::ostream& out);
		bool            process           (int error_check = 1, int suppress = 0);
		bool            process           (int argc, char** argv,
		                                   int error_check = 1,
		                                   int suppress = 0);
		bool            process           (const std::vector<std::string>& argv,
		                                   int error_check = 1,
		                                   int suppress = 0);
		bool            process           (const std::string& argv, int error_check = 1,
		                                   int suppress = 0);
		void            reset             (void);
		void            xverify           (int argc, char** argv,
		                                   int error_check = 1,
		                                   int suppress = 0);
		void            xverify           (int error_check = 1,
		                                   int suppress = 0);
		void            setFlag           (char aFlag);
		void            setModified       (const std::string& optionName,
		                                   const std::string& optionValue);
		void            setOptions        (int argc, char** argv);
		void            setOptions        (const std::vector<std::string>& argv);
		void            setOptions        (const std::string& args);
		void            appendOptions     (int argc, char** argv);
		void            appendOptions     (std::string& args);
		void            appendOptions     (std::vector<std::string>& argv);
		std::ostream&   printRegister     (std::ostream& out);
		int             isDefined         (const std::string& name);
		static std::vector<std::string> tokenizeCommandLine(const std::string& args);
		bool            hasParseError     (void);
		std::string     getParseError     (void);
		std::ostream&   getParseError     (std::ostream& out);

	protected:
		// m_argv: the list of raw command line strings including
		// a mix of options and non-option argument.
		std::vector<std::string> m_argv;

		// m_arguments: list of parsed command-line arguments which
		// are not options, or the command (argv[0]);
		std::vector<std::string> m_arguments;

		// m_optionRegister: store for the states/values of each option.
		std::vector<Option_register*> m_optionRegister;

		// m_optionFlag: the character which indicates an option.
		// Generally a dash, but could be made a slash for Windows environments.
		char m_optionFlag = '-';

		// m_optionList:
		std::map<std::string, int> m_optionList;

		//
		// boolern options for object:
		//

		// m_options_error_check: for .verify() function.
		bool m_options_error_checkQ = true;

		// m_processedQ: true if process() was run.  This will parse
		// the command-line arguments into a list of options, and also
		// enable boolean versions of the options.
		bool m_processedQ = false;

		// m_suppressQ: true means to suppress automatic --options option
		// listing.
		bool m_suppressQ = false;

		// m_optionsArgument: indicate that --options was used.
		bool m_optionsArgQ = false;

		// m_error: used to store errors in parsing command-line options.
		std::stringstream m_error;

	protected:
		int     getRegIndex    (const std::string& optionName);
		bool    isOption       (const std::string& aString, int& argp);
		int     storeOption    (int gargp, int& position, int& running);

};

#define OPTION_BOOLEAN_TYPE   'b'
#define OPTION_CHAR_TYPE      'c'
#define OPTION_DOUBLE_TYPE    'd'
#define OPTION_FLOAT_TYPE     'f'
#define OPTION_INT_TYPE       'i'
#define OPTION_STRING_TYPE    's'
#define OPTION_UNKNOWN_TYPE   'x'



class HumTool : public Options {
	public:
		              HumTool         (void);
		virtual      ~HumTool         ();

		void          clearOutput     (void);

		bool          hasAnyText      (void);
		std::string   getAllText      (void);
		std::ostream& getAllText      (std::ostream& out);

		bool          hasHumdrumText  (void);
		std::string   getHumdrumText  (void);
		std::ostream& getHumdrumText  (std::ostream& out);
		void          suppressHumdrumFileOutput(void);

		bool          hasJsonText     (void);
		std::string   getJsonText     (void);
		std::ostream& getJsonText     (std::ostream& out);

		bool          hasFreeText     (void);
		std::string   getFreeText     (void);
		std::ostream& getFreeText     (std::ostream& out);

		bool          hasWarning      (void);
		std::string   getWarning      (void);
		std::ostream& getWarning      (std::ostream& out);

		bool          hasError        (void);
		std::string   getError        (void);
		std::ostream& getError        (std::ostream& out);
		void          setError        (const std::string& message);

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
// TEXT_INTERFACE -- Expects one text file, either from the
//    first command-line argument (left over after options have been
//    parsed out), or from standard input.
//
// function call that the interface must implement:
//  .run(const string& instring, ostream& out)
//
//

#define TEXT_INTERFACE(CLASS)                          \
int main(int argc, char** argv) {                      \
	hum::CLASS interface;                               \
	if (!interface.process(argc, argv)) {               \
		interface.getError(std::cerr);                   \
		return -1;                                       \
	}                                                   \
	string instring;                                    \
	if (interface.getArgCount() > 0) {                  \
		ifstream input(interface.getArgument(1));        \
		if (!input) {                                    \
			throw std::runtime_error("Could not open file: " + interface.getArgument(1)); \
		}                                                \
		stringstream buf;                                \
		buf << input.rdbuf();                            \
		instring = buf.str();                            \
	} else {                                            \
		stringstream buf;                                \
		buf << cin.rdbuf();                              \
		instring = buf.str();                            \
	}                                                   \
	int status = interface.run(instring, std::cout);    \
	interface.finally();                                \
	if (interface.hasWarning()) {                       \
		interface.getWarning(std::cerr);                 \
		return 0;                                        \
	}                                                   \
	if (interface.hasError()) {                         \
		interface.getError(std::cerr);                   \
		return -1;                                       \
	}                                                   \
	return !status;                                     \
}



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
	interface.finally();                                \
	if (interface.hasWarning()) {                       \
		interface.getWarning(std::cerr);                 \
		return 0;                                        \
	}                                                   \
	if (interface.hasError()) {                         \
		interface.getError(std::cerr);                   \
		return -1;                                       \
	}                                                   \
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
	}                                                                       \
	interface.finally();                                                    \
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
			cout << infiles[i];                                               \
		}                                                                    \
	}                                                                       \
	interface.clearOutput();                                                \
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
	interface.finally();                                                    \
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
	interface.finally();                                                    \
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
	interface.clearOutput();                                                \
	return !status;                                                         \
}



class HumdrumFileSet;

class HumdrumFileStream {
	public:
		                HumdrumFileStream  (void);
		                HumdrumFileStream  (char** list);
		                HumdrumFileStream  (const std::vector<std::string>& list);
		                HumdrumFileStream  (Options& options);
		                HumdrumFileStream  (const std::string& datastream);

		void            loadString         (const std::string& data);

		int             setFileList        (char** list);
		int             setFileList        (const std::vector<std::string>& list);

		void            clear              (void);
		int             eof                (void);

		int             getFile            (HumdrumFile& infile);
		int             read               (HumdrumFile& infile);
		int             read               (HumdrumFileSet& infiles);
		int             readSingleSegment  (HumdrumFileSet& infiles);

	protected:
		std::stringstream m_stringbuffer;   // used to read files from a string
		std::ifstream     m_instream;       // used to read from list of files
		std::stringstream m_urlbuffer;      // used to read data over internet
		std::string       m_newfilebuffer;  // used to keep track of !!!!segment:
		                                    // records.

		std::vector<std::string>  m_filelist;       // used when not using cin
		int                       m_curfile;        // index into filelist

		std::vector<std::string>  m_universals;     // storage for universal comments

		// Automatic URL downloading of data from internet in read():
		void     fillUrlBuffer            (std::stringstream& uribuffer,
		                                   const std::string& uriname);

};



///////////////////////////////////////////////////////////////////////////

class HumdrumFileSet {
   public:
                            HumdrumFileSet   (void);
                            HumdrumFileSet   (Options& options);
                            HumdrumFileSet   (const std::string& contents);
                           ~HumdrumFileSet   ();

      void                  clear            (void);
      void                  clearNoFree      (void);
      int                   getSize          (void);
      int                   getCount         (void) { return getSize(); }
      HumdrumFile&          operator[]       (int index);
		bool                  swap             (int index1, int index2);
		bool                  hasFilters       (void);
		bool                  hasGlobalFilters    (void);
		bool                  hasUniversalFilters (void);
		std::vector<HLp>      getUniversalReferenceRecords(void);

      int                   readFile         (const std::string& filename);
      int                   readString       (const std::string& contents);
      int                   readStringCsv    (const std::string& contents);
      int                   read             (std::istream& inStream);
      int                   read             (Options& options);
      int                   read             (HumdrumFileStream& instream);

      int                   readAppendFile   (const std::string& filename);
      int                   readAppendString (const std::string& contents);
      int                   readAppendStringCsv (const std::string& contents);
      int                   readAppend       (std::istream& inStream);
      int                   readAppend       (Options& options);
      int                   readAppend       (HumdrumFileStream& instream);
      int                   readAppendHumdrum(HumdrumFile& infile);
		int                   appendHumdrumPointer(HumdrumFile* infile);

   protected:
      std::vector<HumdrumFile*>  m_data;

      void                  appendHumdrumFileContent(const std::string& filename,
                                               std::stringstream& inbuffer);
};



class Tool_1520ify : public HumTool {
	public:
		            Tool_1520ify       (void);
		           ~Tool_1520ify       () {};

		bool        run                (HumdrumFileSet& infiles);
		bool        run                (HumdrumFile& infile);
		bool        run                (const std::string& indata, std::ostream& out);
		bool        run                (HumdrumFile& infile, std::ostream& out);

	protected:
		void        initialize         (HumdrumFile& infile);
		void        processFile        (HumdrumFile& infile);
		void        updateKeySignatures(HumdrumFile& infile, int lineindex);
		void        checkDataLine      (HumdrumFile& infile, int lineindex);
		void        clearStates        (void);
		void        addBibliographicRecords(HumdrumFile& infile);
		void        deleteBreaks       (HumdrumFile& infile);
		void        fixEditorialAccidentals(HumdrumFile& infile);
		void        fixInstrumentAbbreviations(HumdrumFile& infile);
		void        addTerminalLongs   (HumdrumFile& infile);
		void        deleteDummyTranspositions(HumdrumFile& infile);
		std::string getDate            (void);
		int         getYear            (void);
		void        adjustSystemDecoration(HumdrumFile& infile);

	private:
		std::vector<std::vector<int>>  m_pstates;
		std::vector<std::vector<int>>  m_kstates;
		std::vector<std::vector<bool>> m_estates;

};


class Tool_addic : public HumTool {
	public:
		         Tool_addic        (void);
		        ~Tool_addic        () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

		int      getInstrumentCodeIndex(HumdrumFile& infile);
		int      getInstrumentClassIndex(HumdrumFile& infile);
		void     updateInstrumentClassLine(HumdrumFile& infile, int codeIndex, int classIndex);
		std::string makeClassLine(HumdrumFile& infile, int codeIndex);
		std::string getInstrumentClass(const std::string& code);


	protected:
		void     initialize        (void);
		void     processFile       (HumdrumFile& infile);

	private:
		std::vector<std::pair<std::string, std::string>> m_instrumentList;
		bool m_fixQ = false;  // used with -f option: fix incorrect instrument classes


};


class Tool_addkey : public HumTool {
	public:
		         Tool_addkey     (void);
		        ~Tool_addkey     () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void    processFile        (HumdrumFile& infile);
		void    initialize         (void);
		void    getLineIndexes     (HumdrumFile& infile);
		void    insertReferenceKey (HumdrumFile& infile);
		void    addInputKey        (HumdrumFile& infile);
		void    insertKeyDesig     (HumdrumFile& infile, const std::string& keyDesig);
		void    printKeyDesig      (HumdrumFile& infile, int index, const std::string& desig, int direction);

	private:
		std::string m_key;
		bool        m_keyQ           = false;
		bool        m_addKeyRefQ     = false;

		int         m_exinterpIndex  = -1;
		int         m_refKeyIndex    = -1;
		int         m_keyDesigIndex  = -1;
		int         m_keySigIndex    = -1;
		int         m_dataStartIndex = -1;

};


class Tool_addlabels : public HumTool {
	public:
		         Tool_addlabels     (void);
		        ~Tool_addlabels     () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void    processFile        (HumdrumFile& infile);
		void    initialize         (void);
		int     getExpansionIndex  (HumdrumFile& infile);
		void    printExpansionLists(HumdrumFile& infile, int index);
		void    assignLabels       (std::vector<std::string>& llist, HumdrumFile& infile);
		void    addLabel           (std::vector<std::string>& llist, HumdrumFile& infile,
		                            int barnum, int subbarnum, const std::string& label);
	private:
		std::string m_default;             // set with the -d option
		std::string m_norep;               // set with the -r option
		std::string m_zeroth;              // m0 label (right after default and norep expansion lists)
		int m_defaultIndex = -1;           // line to place default expansions list above (and then norep)
		std::vector<int> m_barnums;        // set with -l option
		std::vector<int> m_subbarnums;     // set with -l option
		std::vector<std::string> m_labels; // set with -l option
};


class Tool_addtempo : public HumTool {
	public:
		         Tool_addtempo     (void);
		        ~Tool_addtempo     () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void    processFile        (HumdrumFile& infile);
		void    initialize         (void);
		void    assignTempoChanges (std::vector<double>& tlist, HumdrumFile& infile);
		void    addTempo           (std::vector<double>& tlist, HumdrumFile& infile, int measure, double tempo, int offset);
		void    addTempoToStart    (std::vector<double>& tlist, HumdrumFile& infile, double tempo);

	private:
		// tuple<measure, tempo, mesure offset>
		std::vector<std::tuple<int, double, int>> m_tempos;

};


class Tool_autoaccid : public HumTool {
	public:
		             Tool_autoaccid    (void);
		            ~Tool_autoaccid    () {};

		bool         run               (HumdrumFileSet& infiles);
		bool         run               (HumdrumFile& infile);
		bool         run               (const std::string& indata, std::ostream& out);
		bool         run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void        processFile        (HumdrumFile& infile);
		void        initialize         (void);
		void        addAccidentalInfo  (HTp token);
		void        removeAccidentalQualifications(HumdrumFile& infile);
		void        addAccidentalQualifications(HumdrumFile& infile);
		std::string setVisualState     (const std::string& input, bool state);

	private:
		bool         m_visualQ;
		bool         m_hiddenQ;
		bool         m_removeQ;
		bool         m_cautionQ;

};



class Tool_autobeam : public HumTool {
	public:
		             Tool_autobeam       (void);
		            ~Tool_autobeam       () {};

		bool         run                 (HumdrumFile& infile);
		bool         run                 (HumdrumFileSet& infiles);
		bool         run                 (const std::string& indata, std::ostream& out);
		bool         run                 (HumdrumFile& infile, std::ostream& out);

	protected:
		void         initialize          (HumdrumFile& infile);
		void         processStrand       (HTp strandstart, HTp strandend);
		void         processMeasure      (std::vector<HTp>& measure);
		void         addBeam             (HTp startnote, HTp endnote);
		void         addBeams            (HumdrumFile& infile);
		void         beamGraceNotes      (HumdrumFile& infile);
		std::string  getBeamFromDur      (HTp token, const std::string& text);
		void         removeQqMarks       (HTp stok, HTp etok);
		void         removeQqMarks       (HTp tok);
		void         removeBeams         (HumdrumFile& infile);
		void         removeEdgeRests     (HTp& startnote, HTp& endnote);
		void         breakBeamsByLyrics  (HumdrumFile& infile);
		void         processStrandForLyrics(HTp stok, HTp etok);
		bool         hasSyllable         (HTp token);
		void         splitBeam           (HTp tok, HTp stok, HTp etok);
		void         splitBeam2          (std::vector<HTp>& group, HTp tok);
		void         getBeamedNotes      (std::vector<HTp>& toks, HTp tok, HTp stok, HTp etok);
		bool         isLazy              (std::vector<HTp>& group);
		void         splitBeamLazy       (std::vector<HTp>& group, HTp tok);
		void         splitBeamNotLazy    (std::vector<HTp>& group, HTp tok);
		void         removeBeamCharacters(HTp token);

	private:
		std::vector<std::vector<std::pair<int, HumNum> > > m_timesigs;
		std::vector<HTp> m_kernspines;
		bool        m_overwriteQ = false;
		std::vector<bool> m_tracks;
		bool        m_includerests = false;
		int         m_splitcount = 0;
		HumNum      m_duration = 0;

};


class Tool_autocadence : public HumTool {
	class CadenceDefinition {
		public:
			std::string m_funcL;
			std::string m_funcU;
			std::string m_name;
			std::string m_regex;
			void setDefinition(const std::string& funcL, const std::string& funcU,
					const std::string& name, const std::string& regex) {
				m_funcL = funcL;
				m_funcU = funcU;
				m_name = name;
				m_regex = regex;
				// int count = std::count(text.begin(), text.end(), target);
			}
	};

	public:
		            Tool_autocadence           (void);
		           ~Tool_autocadence           () {};

		bool        run                 (HumdrumFileSet& infiles);
		bool        run                 (HumdrumFile& infile);
		bool        run                 (const std::string& indata, std::ostream& out);
		bool        run                 (HumdrumFile& infile, std::ostream& out);
		void        initialize          (void);

	protected:
		void        processFile         (HumdrumFile& infile);
		void        generateCounterpointStrings(std::vector<HTp>& kspines, int indexL, int indexU);
		std::string generateCounterpointString(std::vector<std::vector<HTp>>& pairings, int index);
      void        printModules        (std::vector<std::string>& modules, int lowerPart, int upperPart);
		void        fillNotes           (std::vector<HTp>& voice, HTp exinterp);
		std::string getDiatonicIntervalString  (int lower, int upper);
		int         getDiatonicInterval        (int lower, int upper);
		void        prepareCadenceDefinitions  (void);
		void        addCadenceDefinition       (const std::string& funcL, const std::string& funcU,
		                                        const std::string& name, const std::string& regex);
		void        prepareLowestPitches       (void);
		void        preparePitchInfo           (HumdrumFile& infile);
		void        prepareDiatonicPitches     (HumdrumFile& infile);
		void        printExtractedPitchInfo    (HumdrumFile& infile);
		void        printExtractedIntervalInfo (HumdrumFile& infile);
		void        prepareIntervalInfo        (HumdrumFile& infile);
		int         getPairIndex               (HTp lowerExInterp, HTp upperExInterp);
		void        prepareTrackToVoiceIndex   (HumdrumFile& infile, std::vector<HTp> kspines);
		void        printIntervalManipulatorLine(HumdrumFile& infile, int index, int kcount);
		void        printIntervalDataLine      (HumdrumFile& infile, int index, int kcount);
		void        printIntervalDataLineScore (HumdrumFile& infile, int index, int kcount);
		void        printIntervalLine          (HumdrumFile& infile, int index, int kcount, const std::string& tok);
		void        prepareAbbreviations       (HumdrumFile& infile);
		void        prepareIntervalSequences   (HumdrumFile& infile);
		void        prepareSinglePairSequences (HumdrumFile& infile, int vindex, int pindex);
		std::string generateSequenceString     (HumdrumFile& infile, int lindex, int vindex, int pindex);
		void        printSequenceInfo          (void);
		void        printSequenceMatches       (void);
		void        printSequenceMatches2      (void);
		void        searchIntervalSequences    (void);
		void        printScore                 (HumdrumFile& infile);
		void        printMatchCount            (void);
		void        markupScore                (HumdrumFile& infile);
		void        addMatchToScore            (HumdrumFile& infile, int matchIndex);
		int         getRegexSliceCount         (const std::string& regex);
		void        colorNotes                 (HTp startTok, HTp endTok);
		void        prepareDefinitionList      (std::set<int>& list);
		void        printRegexTable            (void);
		void        printDefinitionRow         (int index);
		void        prepareCvfNames            (void);
		void        prepareDissonanceNames     (void);
		std::string getFunctionNames           (const std::string& input);
		std::string getDissonanceNames         (const std::string& input);
		void        highlightNoteAttack        (HTp startTok);
		bool        getCadenceEndSliceNotes    (HTp& endL, HTp& endU, int count, HumdrumFile& infile,
		                                        int lindex, int vindex, int pindex);
		void        prepareDissonances         (HumdrumFile& infile);
		void        prepareDissonancesForLine  (HumdrumLine& iline, HumdrumLine& dline);
		void        identifySuspensionsAndAgents(HumdrumFile& infile);

	private:

		// m_definitions: A list of the cadence regular expression definitions.
		std::vector<Tool_autocadence::CadenceDefinition> m_definitions;

		// m_pitches: A list of the diatonic pitches for the score, organized
		// in a 2-D array that matches the line/field number of the notes.
		// Middle C is 28, rests are 0, and negative values are sustained
		// pitches.
		std::vector<std::vector<int>> m_pitches;

		// m_lowestPitch: the lowest sounding pitch at every instance in the score.
		// the pitch is stored as an absolute diatonic pitch, middle C is 28, 0 is a rest
		std::vector<int> m_lowestPitch;

		// m_intervals: The counterpoint intervals for each pair of notes.
		// The data is store in a 3-D vector, where the first dimension is the
		// line in the score, the second dimension is the voice (kern spine) index in
		// the score for the lower voice.  For example, if the score has four **kern
		// spines, the second dimension size will be four, and the third dimensions
		// will be 3, 2, 1 and 0.  
		// Dimensions:
		//     0: line index in the Humdrum data
		//     1: voice index of the lower voice
		//     2: pairing interval of two voice generating the interval
		// Parameters for tuple:
		//     0: interval string for the note pair (or empty if no interval.
		//     1: the token for the lower voice note
		//     2: the token for the upper voice note
		std::vector<std::vector<std::vector<std::tuple<std::string, HTp, HTp>>>> m_intervals;

		// m_sequences: The counterpoint interval strings which are searched
		// with the regular expressions in m_definitions.
		// Dimensions:
		//    0: voice index
		//    1: voice pair index
		//    2: an array of tuples, only one which is used.  zero length means no sequence.
		// Parameters for tuple:
		//    0: sequence to search
		//    1: first note of sequence in score (lower voice)
		//    2: first note of sequence in score (upper voice)
		//    3: vector of ints listing matches where int is the m_definitions index(es) that match.
		std::vector<std::vector<std::vector<std::tuple<std::string, HTp, HTp, std::vector<int>>>>> m_sequences;

		// m_matches: List of sequences that match to a cadence formula.  The list contains
		// the vindex, pindex, and nth sequence in m_sequences.
		std::vector<std::vector<int>> m_matches;

		// m_trackToVoiceIndex: Mapping from track to voice index (starting with 0)
		// for the lowest voice).
		std::vector<int> m_trackToVoiceIndex;

		// m_abbr: voice abbreviations to prefix interval data in score for voices.
		// Indexed by voice (lowest = 0).
		std::vector<std::string> m_abbr;

		// m_functionNames: mapping from CVF abbreviation to full name of CFV.
		std::map<std::string, std::string> m_functionNames;

		// m_dissonanceNames: mapping from dissonance abbreviation to full name of dissonance.
		std::map<std::string, std::string> m_dissonanceNames;

		bool m_hasSuspensionMarkersQ = false;

		// options:
		bool m_intervalsQ               = false; // -i: show counterpoint interval infomation
		bool m_intervalsOnlyQ           = false; // -I: show counterpoint interval infomation but
		                                         //     do not do cadence analysis
		bool m_printRawDiatonicPitchesQ = false; // -p: display m_pitches after filling
		int  m_sequenceLength           = 7;     // maximum regex interval sequence length
		bool m_matchesQ                 = false; // -m: display sequences that match to cadence formula(s)
		bool m_printSequenceInfoQ       = false; // -s: print list of interval sequences
		bool m_countQ                   = false; // --count: print number of cadences found
		bool m_colorQ                   = false; // -c: color matched cadence formula
		std::string m_color      = "dodgerblue"; // --color "string" to set matched notes to a specific color
		bool m_showFormulaIndexQ        = false; // -f: show formulation index after CVF label
		bool m_evenNoteSpacingQ         = false; // -e: compress notation (verovio option evenNoteSpacing)
		bool m_regexQ                   = false; // -r: show table of matched regular expressions
		bool m_popupQ                   = true;  // --pop: show popup when hoving over CFV lables (to be implemented)
		bool m_nobackQ                  = false; // -B: don't highlight start of sustain at start of cadence definition
		bool m_showSuspensionsQ         = true;  // !-S: show suspension/agent labels in output score
		bool m_lowestQ                  = false; // -l: use lowest note to define suspensions instead of dissonance analysis
		std::string m_marker = "@";
		std::string m_suspensionMarker = "N";
		std::string m_suspensionColor  = "crimson";
};



class Coord {
   public:
           Coord(void) { clear(); }
      void clear(void) { i = j = -1; }
      int i;
      int j;
};


class Tool_autostem : public HumTool {
	public:
		         Tool_autostem         (void);
		        ~Tool_autostem         () {};

		bool     run                   (HumdrumFileSet& infiles);
		bool     run                   (HumdrumFile& infile);
		bool     run                   (const std::string& indata, std::ostream& out);
		bool     run                   (HumdrumFile& infile, std::ostream& out);

	protected:
		void     initialize            (HumdrumFile& infile);
		void      example              (void);
		void      usage                (void);
		bool      autostem             (HumdrumFile& infile);
		void      getClefInfo          (std::vector<std::vector<int>>& baseline,
		                                HumdrumFile& infile);
		void      addStem              (std::string& input, const std::string& piece);
		void      processKernTokenStemsSimpleModel(HumdrumFile& infile,
		                                std::vector<std::vector<int>>& baseline,
		                                int row, int col);
		void      removeStems          (HumdrumFile& infile);
		void      removeStem2          (HumdrumFile& infile, int row, int col);
		int       getVoice             (HumdrumFile& infile, int row, int col);
		void      getNotePositions     (std::vector<std::vector<std::vector<int>>>& notepos,
		                                std::vector<std::vector<int>>& baseline,
		                                HumdrumFile& infile);
		void      printNotePositions   (HumdrumFile& infile,
		                                std::vector<std::vector<std::vector<int>>>& notepos);
		void      getVoiceInfo         (std::vector<std::vector<int>>& voice, HumdrumFile& infile);
		void      printVoiceInfo       (HumdrumFile& infile, std::vector<std::vector<int>>& voice);
		void      processKernTokenStems(HumdrumFile& infile,
		                                std::vector<std::vector<int>>& baseline, int row, int col);
		void      getMaxLayers         (std::vector<int>& maxlayer, std::vector<std::vector<int>>& voice,
		                                HumdrumFile& infile);
		bool      assignStemDirections (std::vector<std::vector<int>>& stemdir,
		                                std::vector<std::vector<int>> & voice,
		                                std::vector<std::vector<std::vector<int>>>& notepos,
		                                HumdrumFile& infile);
		void      assignBasicStemDirections(std::vector<std::vector<int>>& stemdir,
		                                std::vector<std::vector<int>>& voice,
		                                std::vector<std::vector<std::vector<int>>>& notepos,
		                                HumdrumFile& infile);
		int       determineChordStem   (std::vector<std::vector<int>>& voice,
		                                std::vector<std::vector<std::vector<int>>>& notepos,
		                                HumdrumFile& infile, int row, int col);
		void      insertStems          (HumdrumFile& infile,
		                                std::vector<std::vector<int>>& stemdir);
		void      setStemDirection     (HumdrumFile& infile, int row, int col,
		                                int direction);
		bool      getBeamState         (std::vector<std::vector<std::string >>& beams,
		                                HumdrumFile& infile);
		void      countBeamStuff       (const std::string& token, int& start, int& stop,
		                                int& flagr, int& flagl);
		void      getBeamSegments      (std::vector<std::vector<Coord>>& beamednotes,
		                                std::vector<std::vector<std::string >>& beamstates,
		                                HumdrumFile& infile, std::vector<int> maxlayer);
		int       getBeamDirection     (std::vector<Coord>& coords,
		                                std::vector<std::vector<int>>& voice,
		                                std::vector<std::vector<std::vector<int>>>& notepos);
		void      setBeamDirection     (std::vector<std::vector<int>>& stemdir,
		                                std::vector<Coord>& bnote, int direction);

	private:
		int    debugQ        = 0;       // used with --debug option
		int    removeQ       = 0;       // used with -r option
		int    noteposQ      = 0;       // used with -p option
		int    voiceQ        = 0;       // used with --voice option
		int    removeallQ    = 0;       // used with -R option
		int    overwriteQ    = 0;       // used with -o option
		int    overwriteallQ = 0;       // used with -O option
		int    Middle        = 4;       // used with -u option
		int    Borderline    = 0;       // really used with -u option
		int    notlongQ      = 0;       // used with -L option
		bool   m_quit        = false;

};


class Tool_barnum : public HumTool {
	public:
		         Tool_barnum          (void);
		        ~Tool_barnum          () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:

		void     processFile             (HumdrumFile& infile);
		void     initialize              (void);
		void     removeBarNumbers        (HumdrumFile& infile);
		void     printWithoutBarNumbers  (HumdrumLine& humline);
		void     printWithBarNumbers     (HumdrumLine& humline, int measurenum);
		void     printSingleBarNumber    (const std::string& astring, int measurenum);
		int      getEndingBarline        (HumdrumFile& infile);


	private:
   	bool m_removeQ;
   	int m_startnum;
   	bool m_debugQ;
   	bool m_allQ;

};


class Tool_binroll : public HumTool {
	public:
		         Tool_binroll      (void);
		        ~Tool_binroll      () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void     processFile       (HumdrumFile& infile);
		void     processStrand     (std::vector<std::vector<char>>& roll, HTp starting,
		                            HTp ending);
		void     printAnalysis     (HumdrumFile& infile,
		                            std::vector<std::vector<char>>& roll);

	private:
		HumNum    m_duration;

};


class Tool_bstyle : public HumTool {

	public:
		     Tool_bstyle (void);
		     ~Tool_bstyle() {};

		bool run     (HumdrumFileSet& infiles);
		bool run     (HumdrumFile& infile);
		bool run     (const std::string& indata, std::ostream& out);
		bool run     (HumdrumFile& infile, std::ostream& out);

	protected:
		void         initialize   (void);
      void         processFile  (HumdrumFile& infile);
		void         removeBarStylings(HumdrumFile& infile);
		void         removeBarStylings(HTp spine);
		void         applyBarStylings(HumdrumFile& infile);
		void         applyBarStylings(HTp spine);

	private:
		bool  m_removeQ = false;  // used with -r option

};


class Tool_chantize : public HumTool {
	public:
		                  Tool_chantize             (void);
		                 ~Tool_chantize             () {};

		bool              run                       (HumdrumFileSet& infiles);
		bool              run                       (HumdrumFile& infile);
		bool              run                       (const std::string& indata, std::ostream& out);
		bool              run                       (HumdrumFile& infile, std::ostream& out);

	protected:
		void              initialize                (HumdrumFile& infile);
		void              processFile               (HumdrumFile& infile);
		void              outputFile                (HumdrumFile& infile);
		void              updateKeySignatures       (HumdrumFile& infile, int lineindex);
		void              checkDataLine             (HumdrumFile& infile, int lineindex);
		void              clearStates               (void);
		void              addBibliographicRecords   (HumdrumFile& infile);
		void              deleteBreaks              (HumdrumFile& infile);
		void              fixEditorialAccidentals   (HumdrumFile& infile);
		void              fixInstrumentAbbreviations(HumdrumFile& infile);
		void              deleteDummyTranspositions (HumdrumFile& infile);
		std::string       getDate                   (void);
		std::vector<bool> getTerminalRestStates      (HumdrumFile& infile);
		bool              hasDiamondNotes           (HumdrumFile& infile);

	private:
		std::vector<std::vector<int>>  m_pstates;
		std::vector<std::vector<int>>  m_kstates;
		std::vector<std::vector<bool>> m_estates;
		bool m_diamondQ = false;
};


class Tool_chint : public HumTool {
	public:
		         Tool_chint          (void);
		        ~Tool_chint          () {};

		bool     run                 (HumdrumFileSet& infiles);
		bool     run                 (HumdrumFile& infile);
		bool     run                 (const std::string& indata, std::ostream& out);
		bool     run                 (HumdrumFile& infile, std::ostream& out);

	protected:
		void    processFile          (HumdrumFile& infile);
		void    initialize           (void);
		void    fillIntervalNames    (void);
		void    fillIntervalNamesDiatonic(void);
		void    chromaticColoring    (void);
		void    dissonanceColoring   (void);
		void    getPartIntervals     (std::vector<int>& topInterval,
		                              std::vector<int>& botInterval,
		                              HTp botSpine, HTp topSpine, HumdrumFile& infile);
		void    insertPartColors     (HumdrumFile& infile, std::vector<int>& botInterval,
		                              std::vector<int>& topInterval, int botTrack, int topTrack);
		std::string getColorToken    (int interval, HumdrumFile& infile, int line, HTp token);
		std::string getIntervalToken (int interval, HumdrumFile& infile, int line);

	private:
		// m_color: Color mapping for notes, indexed by base-40:
		std::vector<std::string> m_color;

		// m_intervals: Names of intervals indexed by base-40:
		std::vector<std::string> m_intervals;

		// Used in particular to avoid adding interval when both
		// staves have tied notes:
		std::vector<std::string>  m_botPitch;
		std::vector<std::string>  m_topPitch;

		// m_intervalQ: Show interval numbers
		bool m_intervalQ = false;

		// m_octaveQ: Do not collapse octaves to unisons.
		bool m_octaveQ = false;

		// m_noColorBotQ: Do not colorize bottom analysis staff
		bool m_noColorBotQ = false;

		// m_noColortopQ: Do not colorize top analysis staff
		bool m_noColorTopQ = false;

		// m_negativeQ: Add minus sign to intervals
		// when staff notes are crossed.
		bool m_negativeQ = false;

		// m_middle: Add intervals between analysis staves, or actually
		// below top staff. (Only effective in JavaScript compiled code.)
		bool m_middleQ = true;

};


class Tool_chooser : public HumTool {
	public:
		       	   Tool_chooser       (void);
		       	  ~Tool_chooser       () {};

		bool        run                (HumdrumFileSet& infiles);
		bool        run                (const std::string& indata);
		bool        run                (HumdrumFileStream& instream);

	protected:
		void        processFiles       (HumdrumFileSet& infiles);
		void        initialize         (void);

		void        expandSegmentList  (std::vector<int>& field, std::string& fieldstring,
		                                int maximum);
		void        processSegmentEntry(std::vector<int>& field,
		                                const std::string& astring, int maximum);
		void        removeDollarsFromString(std::string& buffer, int maximum);

	private:

};


class Tool_chord : public HumTool {
	public:
		         Tool_chord      (void);
		        ~Tool_chord      () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void     processFile       (HumdrumFile& infile, int direction);
		void     processChord      (HTp tok, int direction);
		void     initialize        (void);
		void     minimizeChordPitches(std::vector<std::string>& notes, std::vector<std::pair<int, int>>& pitches);
		void     maximizeChordPitches(std::vector<std::string>& notes, std::vector<std::pair<int, int>>& pitches);

	private:
		int       m_direction = 0;
		int       m_spine     = -1;
		int       m_primary   = 0;

};


class NoteNode {
   public:
		int b40;         // base-40 pitch number or 0 if a rest, negative if tied
		int line;        // line number in original score of note
		int spine;       // spine number in original score of note
		int measure;     // measure number of note
		int serial;      // serial number
		int mark;        // for marking search matches
		std::string notemarker;  // for pass-through of marks
		double beatsize; // time signature bottom value which or
		                 // 3 times the bottom if compound meter
		HumNum   duration;  // duration

		         NoteNode             (void) { clear(); }
		         NoteNode             (const NoteNode& anode);
		         NoteNode& operator=  (NoteNode& anode);
		        ~NoteNode             (void);
		void     clear                (void);
		int      isRest               (void) { return b40 == 0 ? 1 : 0; }
		int      isSustain            (void) { return b40 < 0 ? 1 : 0; }
		int      isAttack             (void) { return b40 > 0 ? 1 : 0; }
		int      getB40               (void) { return abs(b40); }
		void     setId                (const std::string& anid);
		std::string   getIdString          (void);
		std::string   getId                (void);

   protected:
		std::string  protected_id; // id number provided by data
};



class Tool_cint : public HumTool {
	public:
		         Tool_cint    (void);
		        ~Tool_cint    () {};

		bool     run                    (HumdrumFileSet& infiles);
		bool     run                    (HumdrumFile& infile);
		bool     run                    (const std::string& indata, ostream& out);
		bool     run                    (HumdrumFile& infile, ostream& out);

	protected:

		void      initialize           (void);
		void      example              (void);
		void      usage                (const std::string& command);
		int       processFile          (HumdrumFile& infile);
		void      getKernTracks        (std::vector<int>& ktracks, HumdrumFile& infile);
		int       validateInterval     (std::vector<std::vector<NoteNode> >& notes,
		                                int i, int j, int k);
		void      printIntervalInfo    (HumdrumFile& infile, int line,
		                                int spine, std::vector<std::vector<NoteNode> >& notes,
		                                int noteline, int noteindex,
		                                std::vector<std::string >& abbr);
		void      getAbbreviations     (std::vector<std::string >& abbreviations,
		                                std::vector<std::string >& names);
		void      getAbbreviation      (std::string& abbr, std::string& name);
		void      extractNoteArray     (std::vector<std::vector<NoteNode> >& notes,
		                                HumdrumFile& infile, std::vector<int>& ktracks,
		                                std::vector<int>& reverselookup);
		int       onlyRests            (std::vector<NoteNode>& data);
		int       hasAttack            (std::vector<NoteNode>& data);
		int       allSustained         (std::vector<NoteNode>& data);
		void      printPitchGrid       (std::vector<std::vector<NoteNode> >& notes,
		                                HumdrumFile& infile);
		void      getNames             (std::vector<std::string >& names,
		                                std::vector<int>& reverselookup, HumdrumFile& infile);
		void      printLattice         (std::vector<std::vector<NoteNode> >& notes,
		                                HumdrumFile& infile, std::vector<int>& ktracks,
		                                std::vector<int>& reverselookup, int n);
		void      printSpacer          (ostream& out);
		int       printInterval        (ostream& out, NoteNode& note1, NoteNode& note2,
		                                int type, int octaveadjust = 0);
		int       printLatticeItem     (std::vector<std::vector<NoteNode> >& notes, int n,
		                                int currentindex, int fileline);
		int       printLatticeItemRows (std::vector<std::vector<NoteNode> >& notes, int n,
		                                int currentindex, int fileline);
		int       printLatticeModule   (ostream& out, std::vector<std::vector<NoteNode> >& notes,
		                                int n, int startline, int part1, int part2);
		void      printInterleaved     (HumdrumFile& infile, int line,
		                                std::vector<int>& ktracks, std::vector<int>& reverselookup,
		                                const std::string& interstring);
		void      printLatticeInterleaved(std::vector<std::vector<NoteNode> >& notes,
		                                HumdrumFile& infile, std::vector<int>& ktracks,
		                                std::vector<int>& reverselookup, int n);
		int       printInterleavedLattice(HumdrumFile& infile, int line,
		                                std::vector<int>& ktracks, std::vector<int>& reverselookup,
		                                int n, int currentindex,
		                                std::vector<std::vector<NoteNode> >& notes);
		int       printCombinations    (std::vector<std::vector<NoteNode> >& notes,
		                                HumdrumFile& infile, std::vector<int>& ktracks,
		                                std::vector<int>& reverselookup, int n,
		                                std::vector<std::vector<std::string> >& retrospective,
		                                const std::string& searchstring);
		void      printAsCombination   (HumdrumFile& infile, int line,
		                                std::vector<int>& ktracks, std::vector<int>& reverselookup,
		                                const std::string& interstring);
		int       printModuleCombinations(HumdrumFile& infile, int line,
		                                std::vector<int>& ktracks, std::vector<int>& reverselookup,
		                                int n, int currentindex,
		                                std::vector<std::vector<NoteNode> >& notes,
		                                int& matchcount,
		                                std::vector<std::vector<std::string> >& retrospective,
		                                const std::string& searchstring);
		int       printCombinationsSuspensions(std::vector<std::vector<NoteNode> >& notes,
		                                HumdrumFile& infile, std::vector<int>& ktracks,
		                                std::vector<int>& reverselookup, int n,
		                                std::vector<std::vector<std::string> >& retrospective);
		int       printCombinationModule(ostream& out, const std::string& filename,
		                                std::vector<std::vector<NoteNode> >& notes,
		                                int n, int startline, int part1, int part2,
		                                std::vector<std::vector<std::string> >& retrospective,
		                                std::string& notemarker, int markstate = 0);
		int       printCombinationModulePrepare(ostream& out, const std::string& filename,
		                                std::vector<std::vector<NoteNode> >& notes, int n,
		                                int startline, int part1, int part2,
		                                std::vector<std::vector<std::string> >& retrospective,
		                                HumdrumFile& infile, const std::string& searchstring);
		int       getOctaveAdjustForCombinationModule(std::vector<std::vector<NoteNode> >& notes,
		                                int n, int startline, int part1, int part2);
		void      addMarksToInputData  (HumdrumFile& infile,
		                                std::vector<std::vector<NoteNode> >& notes,
		                                std::vector<int>& ktracks,
		                                std::vector<int>& reverselookup);
		void      markNote              (HumdrumFile& infile, int line, int col);
		void      initializeRetrospective(std::vector<std::vector<std::string> >& retrospective,
		                                HumdrumFile& infile, std::vector<int>& ktracks);
		int       getTriangleIndex(int number, int num1, int num2);
		void      adjustKTracks        (std::vector<int>& ktracks, const std::string& koption);
		int       getMeasure           (HumdrumFile& infile, int line);

	private:

		int       debugQ       = 0;      // used with --debug option
		int       base40Q      = 0;      // used with --40 option
		int       base12Q      = 0;      // used with --12 option
		int       base7Q       = 0;      // used with -7 option
		int       pitchesQ     = 0;      // used with --pitches option
		int       rhythmQ      = 0;      // used with -r option and others
		int       durationQ    = 0;      // used with --dur option
		int       latticeQ     = 0;      // used with -l option
		int       interleavedQ = 0;      // used with -L option
		int       Chaincount   = 1;      // used with -n option
		int       chromaticQ   = 0;      // used with --chromatic option
		int       sustainQ     = 0;      // used with -s option
		int       zeroQ        = 0;      // used with -z option
		int       topQ         = 0;      // used with -t option
		int       toponlyQ     = 0;      // used with -T option
		int       hparenQ      = 0;      // used with -h option
		int       mparenQ      = 0;      // used with -y option
		int       locationQ    = 0;      // used with --location option
		int       koptionQ     = 0;      // used with -k option
		int       parenQ       = 0;      // used with -p option
		int       rowsQ        = 0;      // used with --rows option
		int       hmarkerQ     = 0;      // used with -h option
		int       mmarkerQ     = 0;      // used with -m option
		int       attackQ      = 0;      // used with --attacks option
		int       rawQ         = 0;      // used with --raw option
		int       raw2Q        = 0;      // used with --raw2 option
		int       xoptionQ     = 0;      // used with -x option
		int       octaveallQ   = 0;      // used with -O option
		int       octaveQ      = 0;      // used with -o option
		int       noharmonicQ  = 0;      // used with -H option
		int       nomelodicQ   = 0;      // used with -M option
		int       norestsQ     = 0;      // used with -R option
		int       nounisonsQ   = 0;      // used with -U option
		int       filenameQ    = 0;      // used with -f option
		int       searchQ      = 0;      // used with --search option
		int       markQ        = 0;      // used with --mark option
		int       countQ       = 0;      // used with --count option
		int       suspensionsQ = 0;      // used with --suspensions option
		int       uncrossQ     = 0;      // used with -c option
		int       retroQ       = 0;      // used with --retro option
		int       idQ          = 0;      // used with --id option
		std::vector<std::string> Ids;    // used with --id option
		std::string NoteMarker;          // used with -N option
		std::string MarkColor;           // used with --color
		std::string SearchString;
		std::string Spacer;

};


class cmr_group_info;


//////////////////////////////
//
// cmr_note_info -- Storage for a single CMR note.
//

class cmr_note_info {

	public:
		         cmr_note_info    (void);
		void     clear            (void);
		int      getMeasureBegin  (void);
		int      getMeasureEnd    (void);
		void     setMeasureBegin  (int measure);
		void     setMeasureEnd    (int measure);
		HumNum   getStartTime     (void);
		HumNum   getEndTime       (void);
		int      getMidiPitch     (void);
		std::string   getPitch         (void);
		HTp      getToken         (void);
		int      getLineIndex     (void);
		double   getNoteStrength  (void);
		bool     hasSyncopation   (void);
		bool     hasLeapBefore    (void);
		void     markNote         (const std::string& marker);
		std::ostream& printNote   (std::ostream& output = std::cout, const std::string& marker = "");

		static double getMetricLevel(HTp token);
		static bool   isSyncopated(HTp token);
		static bool   isLeapBefore(HTp token);

		static double m_syncopationWeight;
		static double m_leapWeight;

	private:
		std::vector<HTp> m_tokens;    // List of tokens for the notes (first entry is note attack);

		// location information:
		int   m_measureBegin;    // starting measure of note
		int   m_measureEnd;      // ending measure of tied note group

		// analysis information:
		int   m_hasSyncopation;  // is the note syncopated
		int   m_hasLeapBefore;   // is there a melodic leap before note

	friend class cmr_group_info;

};



//////////////////////////////
//
// cmr_group_info -- Storage for a CMR note group.
//


class cmr_group_info {
	public:
		        cmr_group_info     (void);
		void    clear              (void);
		int     getIndex           (void);
		int     getMeasureBegin    (void);
		int     getMeasureEnd      (void);
		int     getMidiPitch       (void);
		HTp     getNote            (int index);
		HTp     getToken           (int index) { return getNote(index); }
		HTp     getFirstToken      (void);
		int     getNoteCount       (void);
		int     getTrack           (void);
		int     getStartFieldNumber(void);
		int     getStartLineNumber (void);
		void    addNote            (std::vector<HTp>& tiednotes, std::vector<int>& barnums);
		void    markNotes          (const std::string& marker);
		void    setSerial          (int serial);
		int     getSerial          (void);
		int     getDirection       (void);
		void    setDirectionUp     (void);
		void    setDirectionDown   (void);
		int     getLeapCount       (void);
		int     getSyncopationCount(void);
		void    makeInvalid        (void);
		bool    isValid            (void);
		std::string  getPitch      (void);
		HumNum  getEndTime         (void);
		HumNum  getGroupDuration   (void);
		HumNum  getStartTime       (void);
		double  getGroupStrength   (void);
		bool    mergeGroup         (cmr_group_info& group);
		std::ostream& printNotes   (std::ostream& output = std::cout, const std::string& marker = "");

	private:
		int   m_serial;                     // used to keep track of mergers
		int   m_direction;                  // +1 = positive peak, -1 = negative peak
		std::vector<cmr_note_info> m_notes; // note info for each note in group.
};


///////////////////////////////////////////////////////////////////////////

class Tool_cmr : public HumTool {
	public:
		                 Tool_cmr                (void);
		                ~Tool_cmr                () {};

		bool             run                     (HumdrumFileSet& infiles);
		bool             run                     (HumdrumFile& infile);
		bool             run                     (const std::string& indata, std::ostream& out);
		bool             run                     (HumdrumFile& infile, std::ostream& out);
		void             finally                 (void);

	protected:
		void             processFile             (HumdrumFile& infile);
		void             initialize              (void);
		void             processFile             (HumdrumFile& infile, Options& options);
		void             processSpine            (HTp startok, HumdrumFile& infile);
		void             processSpineFlipped     (HTp startok, HumdrumFile& infile);
		void             identifyLocalPeaks      (std::vector<bool>& cmrnotes,
		                                          std::vector<int>& notelist);
		void             getDurations            (std::vector<double>& durations,
		                                          std::vector<std::vector<HTp>>& notelist);
		void             getBeat                 (std::vector<bool>& metpos,
		                                          std::vector<std::vector<HTp>>& notelist);
		bool             isMelodicallyAccented   (int index);
		bool             hasLeapBefore           (HTp token);
		bool             isSyncopated            (HTp token);
		void             getLocalPeakNotes       (std::vector<std::vector<HTp>>& newnotelist,
		                                          std::vector<std::vector<HTp>>& oldnotelist,
		                                          std::vector<bool>& cmrnotes);
		void             identifyPeakSequence    (std::vector<bool>& globalcmrnotes,
		                                          std::vector<int>& cmrmidinums,
		                                          std::vector<std::vector<HTp>>& notes);
		void             getMidiNumbers          (std::vector<int>& midinotes, std::vector<std::vector<HTp>>& notelist);
		void             getMetlev               (std::vector<double>& metlevs, std::vector<std::vector<HTp>>& notelist);
		void             getSyncopation          (std::vector<bool>& syncopation, std::vector<std::vector<HTp>>& notelist);
		void             getLeapBefore           (std::vector<bool>& leap, std::vector<int>& midinums);
		void             getNoteList             (std::vector<std::vector<HTp>>& notelist, HTp starting);
		void             printData               (std::vector<std::vector<HTp>>& notelist,
		                                          std::vector<int>& midinums,
		                                          std::vector<bool>& cmrnotes);
		void             markNotesInScore        (void);
		void             mergeOverlappingPeaks   (void);
		bool             checkGroupPairForMerger (cmr_group_info& index1, cmr_group_info& index2);
		int              countNotesInScore       (HumdrumFile& infile);
		void             flipMidiNumbers         (std::vector<int>& midinums);
		void             markNotes               (std::vector<std::vector<HTp>>& noteslist, std::vector<bool> cmrnotesQ, const std::string& marker);
		void             prepareHtmlReport       (void);
		void             printAnalysisData       (void);
		int              getGroupCount           (void);
		int              getGroupNoteCount       (void);
		int 						 getStrengthScore        (void);
		void             printStatistics         (HumdrumFile& infile);
		std::string           getComposer             (HumdrumFile& infile);
		void             printSummaryStatistics  (HumdrumFile& infile);
		void             storeVegaData           (HumdrumFile& infile);
		void             printVegaPlot           (void);
		void             printHtmlPlot           (void);
		void             printGroupStatistics    (HumdrumFile& infile);
		void             getPartNames            (std::vector<std::string>& partNames, HumdrumFile& infile);
		void             checkForCmr             (int index, int direction, HumdrumFile& infile);
		bool             hasHigher               (int pitch, int tolerance,
		                                          std::vector<int>& midinums,
		                                          std::vector<std::vector<HTp>>& notelist,
		                                          int index1, int index2);
		bool             hasGroupUp              (void);
		bool             hasGroupDown            (void);
		void             getVocalRange           (std::vector<std::string>& minpitch,
		                                          std::vector<std::string>& maxpitch,
		                                          std::vector<std::vector<HTp>>& notelist);
		std::string      getPitch                (HTp token);
		void             addGroupNumbersToScore  (HumdrumFile& infile);
		void             addGroupNumberToScore   (HumdrumFile& infile, HTp note, int number, int dir);
		void             adjustGroupSerials      (void);
		std::string      getLocalLabelToken      (int number, int dir);
		bool             isOnStrongBeat          (HTp token);

	private:
		// Command-line options:
		bool        m_rawQ        = false;       // don't print score (only analysis)
		bool        m_peaksQ      = false;       // analyze only positive cmrs (peaks)
		bool        m_npeaksQ     = false;       // analyze only negative cmrs (troughs)
		bool        m_naccentedQ  = false;       // analyze cmrs without melodic accentation
		bool        m_infoQ       = false;       // used with -i option: display info only
		bool        m_localQ      = false;       // used with -l option: mark all local peaks
		bool        m_localOnlyQ  = false;       // used with -L option: only mark local peaks, then exit before CMR analysis.
		bool        m_summaryQ    = false;       // used with -S option: summary statistics of multiple files
		bool        m_vegaQ       = false;       // used with -v option: output Vega-lite plot directly
		bool        m_htmlQ       = false;       // used with -V option: output Vega-lite plot in HTML file
		bool        m_vegaCountQ  = false;       // used with -w option: output Vega-lite plot for CMR count
		bool        m_vegaStrengthQ  = false;    // used with -W option: output Vega-lite plot with strength scores
		bool        m_notelistQ   = false;       // used with --notelist option
		bool        m_debugQ      = false;       // used with --debug option
		bool        m_numberQ     = false;       // used with -N option
		double      m_smallRest   = 4.0;         // Ignore rests that are 1 whole note or less
		double      m_cmrDur      = 24.0;        // 6 whole notes maximum between m_cmrNum local maximums
		double      m_cmrNum      = 3;           // number of local maximums in a row needed to mark in score
		int         m_noteCount   = 0;           // total number of notes in the score
		int         m_local_count = 0;           // used for coloring local peaks
		std::string m_colorUp     = "red";       // color to mark peak cmr notes
		std::string m_markerUp    = "+";         // marker to label peak cmr notes in score
		std::string m_colorDown   = "orange";    // color to mark antipeak cmr notes
		std::string m_markerDown  = "@";         // marker to label antipeak cmr notes in score
		std::string m_local_color = "limegreen"; // color to mark local peaks
		std::string m_local_marker = "N";        // marker for local peak notes
		std::string m_leap_color  = "purple";    // color to mark leap notes before peaks
		std::string m_leap_marker = "k";         // marker for leap notes

		// Negative peak markers:
		std::string m_local_color_n = "green";   // color to mark local peaks
		std::string m_local_marker_n = "K";      // marker for local peak notes
		int         m_local_count_n = 0;         // used for coloring local peaks


		// Analysis variables:
		std::vector<std::vector<HTp>> m_notelist; // **kern tokens (each entry is a tied group)
		std::vector<int>    m_barNum;            // starting bar number of lines in input score.

		// m_noteGroups == Storage for analized CMRs.
		std::vector<cmr_group_info> m_noteGroups;

		// m_partNames == Names of the parts (or prefferably abbreviations)
		std::vector<std::string> m_partNames;

		// m_track == Current track being processed.
		int m_track = 0;

		// m_showMergedQ == Show merged groups in output list.
		bool m_showMergedQ = false;

		// m_minPitch == minimum pitch indexed by track (scientific notation);
		std::vector<std::string> m_minPitch;

		// m_maxPitch == minimum pitch indexed by track (scientific notation);
		std::vector<std::string> m_maxPitch;

		// m_durUnit == duration unit for displaying durations in analysis table.
		std::string m_durUnit = "w";

		// m_halfQ == report durations in half note (minims).
		bool m_halfQ = false;

		// variables for doing CMR analysis (reset for each part)
		std::vector<int>         m_midinums;      // MIDI note for first entry for teach tied group
		std::vector<bool>        m_localpeaks;    // True if higher (or lower for negative search) than adjacent notes.
		std::vector<double>      m_metlevs;       // True if higher (or lower for negative search) than adjacent notes.
		std::vector<bool>        m_syncopation;   // True if note is syncopated.
		std::vector<bool>        m_leapbefore;    // True if note has a leap before it.

		// Summary statistics variables:
		std::vector<int>         m_cmrCount;       // number of CMRs in each input file
		std::vector<int>         m_cmrNoteCount;   // number of CMR notes in each input file
		std::vector<int>         m_scoreNoteCount; // number of note in each input file

		std::stringstream        m_vegaData;       // stores all data for Vega plot from each processFile
};



class Tool_colorgroups : public HumTool {
	public:
		         Tool_colorgroups  (void);
		        ~Tool_colorgroups  () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void     processFile       (HumdrumFile& infile);
		void     initialize        (void);

};


class Tool_colortriads : public HumTool {
	public:
		         Tool_colortriads  (void);
		        ~Tool_colortriads  () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void     processFile       (HumdrumFile& infile);
		void     initialize        (void);
		int      getDiatonicTransposition(HumdrumFile& infile);

	private:
		std::vector<int> m_colorState;
		std::vector<std::string> m_color;
		std::vector<std::string> m_searches;
		std::vector<std::string> m_marks;
		bool m_filtersQ  = false;
		bool m_commandsQ = false;
		bool m_relativeQ = false;
		std::string m_key;

};


class Tool_composite : public HumTool {
	public:
		            Tool_composite       (void);
		           ~Tool_composite       () {};

		bool        run                  (HumdrumFileSet& infiles);
		bool        run                  (HumdrumFile& infile);
		bool        run                  (const std::string& indata, std::ostream& out);
		bool        run                  (HumdrumFile& infile, std::ostream& out);

	protected:
		void        processFile               (HumdrumFile& infile);
		void        initialize                (HumdrumFile& infile);
		void        initializeNumericAnalyses (HumdrumFile& infile);
		bool        hasGroupInterpretations   (HumdrumFile& infile);
		void        prepareOutput             (HumdrumFile& infile);
		void        analyzeFullCompositeRhythm(HumdrumFile& infile);
		void        analyzeGroupCompositeRhythms(HumdrumFile& infile);
		void        analyzeCoincidenceRhythms (HumdrumFile& infiel);
		void        assignGroups              (HumdrumFile& infile);
		void        analyzeLineGroups         (HumdrumFile& infile);
		void        analyzeLineGroup          (HumdrumFile& infile, int line,
		                                       const std::string& target);
		void        extractGroup              (HumdrumFile& infile, const std::string &target);
		void        getNumericGroupStates     (std::vector<int>& states, HumdrumFile& infile, const std::string& tgroup);
		int         getGroupNoteType          (HumdrumFile& infile, int line, const std::string& group);
		HumNum      getLineDuration           (HumdrumFile& infile, int index,
		                                       std::vector<int>& isNull);
		void        backfillGroup             (std::vector<std::vector<std::string>>& curgroup,
		                                       HumdrumFile& infile, int line, int track,
		                                       int subtrack, const std::string& group);

		void        getAnalysisOutputLine     (std::ostream& output, HumdrumFile& infile,
		                                       int line);
		std::string getFullCompositeToken     (HumdrumFile& infile, int line);
		std::string getCoincidenceToken       (HumdrumFile& infile, int line);
		std::string getGroupCompositeToken    (HumdrumFile& infile, int line, int group);
		void        getGroupStates            (std::vector<std::vector<int>>& groupstates,
		                                       HumdrumFile& infile);
		void        getGroupDurations         (std::vector<std::vector<HumNum>>& groupdurs,
		                                       std::vector<std::vector<int>>& groupstates,
		                                       HumdrumFile& infile);
		void        getGroupDurations         (std::vector<HumNum>& groupdurs,
		                                       std::vector<int>& groupstates,
		                                       HumdrumFile& infile);
		void        printGroupAssignments     (HumdrumFile& infile);
		void        getGroupRhythms           (std::vector<std::vector<std::string>>& rhythms,
		                                       std::vector<std::vector<HumNum>>& groupdurs,
		                                       std::vector<std::vector<int>>& groupstates,
		                                       HumdrumFile& infile);
		void        getGroupRhythms           (std::vector<std::string>& rhythms,
		                                       std::vector<HumNum>& durs, std::vector<int>& states,
		                                       HumdrumFile& infile);
		int         typeStringToInt           (const std::string& value);
		void        addNumericAnalyses        (std::ostream& output, HumdrumFile& infile, int line,
		                                       std::vector<std::vector<double>>&  rhythmIndex);
		void        analyzeOutputVariables(HumdrumFile& infile);
		std::string getTimeSignature          (HumdrumFile& infile, int line, const std::string& group);
		std::string getMetricSymbol           (HumdrumFile& infile, int line, const std::string& group);
		std::string generateVerseLabelLine    (HumdrumFile& output, HumdrumFile& input, int line);
		std::string generateStriaLine         (HumdrumFile& output, HumdrumFile& input, int line);
		std::string getFullCompositeMarker    (int line);
		void        addStaffInfo              (HumdrumFile& output, HumdrumFile& infile);
		void        addTimeSignatureChanges   (HumdrumFile& output, HumdrumFile& infile);
		void        addMeterSignatureChanges  (HumdrumFile& output, HumdrumFile& infile);
		void        adjustBadCoincidenceRests (HumdrumFile& output, HumdrumFile& infile);
		HTp         fixBadRestRhythm          (HTp token, std::string& rhythm, HumNum tstop, HumNum tsbot);
		std::string generateSizeLine          (HumdrumFile& output, HumdrumFile& input, int line);
		void        convertNotesToRhythms     (HumdrumFile& infile);
		int         getEventCount             (std::vector<std::string>& data);
		void        fixTiedNotes              (std::vector<std::string>& data, HumdrumFile& infile);
		void        doOnsetAnalysisCoincidence(std::vector<double>& output,
		                                       std::vector<double>& inputA, std::vector<double>& inputB);
		void        checkForAutomaticGrouping (HumdrumFile& infile);

		// Numeric analysis functions:
		void        doNumericAnalyses         (HumdrumFile& infile);
		void        doOnsetAnalyses           (HumdrumFile& infile);
		void        doOnsetAnalysis           (std::vector<double>& analysis,
		                                       HumdrumFile& infile,
		                                       const std::string& targetGroup);

		void        doAccentAnalyses          (HumdrumFile& infile);

		void        doOrnamentAnalyses        (HumdrumFile& infile);

		void        doSlurAnalyses            (HumdrumFile& infile);

		void        doTotalAnalyses           (HumdrumFile& infile);

		// Numeric analysis support functions:
		int         countNoteOnsets           (HTp token);

		bool        needsCoincidenceMarker    (int line, bool forceQ = false);
		void        addCoincidenceMarks       (HumdrumFile& infile);

	private:
		bool        m_debugQ      = false;  // used with --debug option
		bool        m_appendQ     = false;  // append analysis data to input data spines
		bool        m_prependQ    = true;   // default position is to place output at start of line
		bool        m_extractQ    = false;  // output only comp. rhythm analyses (no input)
		bool        m_beamQ       = true;   // used with -B option
		bool        m_hasGroupsQ  = false;  // true if contains *grp:(A|B) interpretations
		std::string m_pitch       = "eR";   // pitch to display for composite rhythm
		bool        m_graceQ      = false;  // include grace notes in composite rhythm

		// Composite rhythm analysis variables:
		bool        m_fullCompositeQ  = true;  // used with -F option
		bool        m_coincidenceQ    = false; // used with -c option
		bool        m_groupsQ         = false; // used with -g option
		bool        m_upstemQ         = false; // used with -u option


		bool        m_onlyQ = false; // used with -o option
		std::string m_only;          // used with -o option

		bool        m_assignedGroups = false; // Have group labels been added to notes?

		// Storage for composite rhythm analysis spines:
		std::vector<std::string> m_fullComposite;
		std::vector<std::string> m_coincidence;
		std::vector<std::vector<std::string>> m_groups;  // Groups A and B

		// Numerical analysis variables:
		bool        m_analysisOnsetsQ    = false;    // used with -P option
		bool        m_analysisAccentsQ   = false;    // used with -A option
		bool        m_analysisOrnamentsQ = false;    // used with -O option
		bool        m_analysisSlursQ     = false;    // used with -S option
		bool        m_analysisTotalQ     = false;    // used with -T option
		std::vector<int> m_analysisIndex;           // -PAOST booleans in array

		bool        m_analysesQ          = false;    // union of -PAOST options
		int         m_numericAnalysisSpineCount = 0; // sum of -PAOST options
		bool        m_nozerosQ           = false;    // used with -Z option

		bool        m_assignedQ          = false;    // used to keep track of group analysis initialization

		// Data storage for numerical anslysis.
		//
		// First index is the rhythm type:
		//    0 index for Coincidence rhythm
		//    1 index for full Composite rhythm
		//    2 index for Group A composite rhythym
		//    3 index for Group B composite rhythym
		//    [4 and higher: index for Group C (future?)]
		//
		// Second index is type of analysis:
		//    0 = onsets
		//    1 = accents
		//    2 = ornaments
		//    3 = slurs
		//    4 = total
		//
		// Third index is line number in original file
		//
		std::vector<std::vector<std::vector<double>>> m_analyses;

		// first two dimension indexes into m_analyses:

		const int m_ANALYSES_DIM1  = 4;
		const int m_COINCIDENCE    = 0;
		const int m_COMPOSITE_FULL = 1;
		const int m_COMPOSITE_A    = 2;
		const int m_COMPOSITE_B    = 3;

		const int m_ANALYSES_DIM2  = 5;
		const int m_ONSET          = 0;
		const int m_ACCENT         = 1;
		const int m_ORNAMENT       = 2;
		const int m_SLUR           = 3;
		const int m_TOTAL          = 4;

		// output line variables (zero means unset, and negative means add
		// before next line.
		int m_clefIndex             = 0;
		int m_striaIndex            = 0;
		int m_sizeIndex             = 0;
		int m_firstDataIndex        = 0;
		int m_instrumentNameIndex   = 0;
		int m_instrumentAbbrIndex   = 0;
		int m_timeSignatureIndex    = 0;
		int m_meterSymbolIndex      = 0;
		int m_groupAssignmentIndex  = 0;
		int m_verseLabelIndex       = 0;

		// analytic counts:
		int m_coincidenceEventCount   = -1; // number of events in coincidence
		int m_fullCompositeEventCount = -1; // number of events in full composite rhythm
		int m_groupAEventCount        = -1; // number of events in group A composite rhythm
		int m_groupBEventCount        = -1; // number of events in group B composite rhythm

		double m_scoreSize          = 100.0;
		double m_analysisSize       = 100.0;

		bool m_eventQ                = false;
		bool m_rhythmQ              = false;
		bool m_colorFullCompositeQ  = false;
		bool m_extractInputQ        = false;
		bool m_coinMarkQ            = false;
		std::string m_coinMark      = "|";
		std::string m_coinMarkColor = "limegreen";
		std::string m_AMark         = "@";
		std::string m_AMarkColor    = "crimson";
		std::string m_BMark         = "Z";
		std::string m_BMarkColor    = "dodgerblue";

};


class Tool_compositeold : public HumTool {
	public:
		            Tool_compositeold        (void);
		           ~Tool_compositeold        () {};

		bool        run                  (HumdrumFileSet& infiles);
		bool        run                  (HumdrumFile& infile);
		bool        run                  (const std::string& indata, std::ostream& out);
		bool        run                  (HumdrumFile& infile, std::ostream& out);

	protected:
		void        processFile          (HumdrumFile& infile);
		void        prepareMultipleGroups(HumdrumFile& infile);
		void        prepareSingleGroup   (HumdrumFile& infile);
		void        initialize           (void);
		void        initializeAnalysisArrays(HumdrumFile& infile);
		int         typeStringToInt      (const std::string& value);
		HumNum      getLineDuration      (HumdrumFile& infile, int index, std::vector<bool>& isNull);
		void        getGroupStates       (std::vector<std::vector<int>>& groupstates, HumdrumFile& infile);
		void        assignGroups         (HumdrumFile& infile);
		void        analyzeLineGroups    (HumdrumFile& infile);
		void        analyzeLineGroup     (HumdrumFile& infile, int line, const std::string& target);
		void        printGroupAssignments(HumdrumFile& infile);
		int         getGroupNoteType     (HumdrumFile& infile, int line, const std::string& group);
		void        getGroupDurations    (std::vector<std::vector<HumNum>>& groupdurs,
		                                  std::vector<std::vector<int>>& groupstates, HumdrumFile& infile);
		void        getGroupDurations    (std::vector<HumNum>& groupdurs, std::vector<int>& groupstates,
		                                  HumdrumFile& infile);
		void        getGroupRhythms      (std::vector<std::vector<std::string>>& rhythms,
		                                  std::vector<std::vector<HumNum>>& groupdurs,
		                                  std::vector<std::vector<int>>& groupstates,
		                                  HumdrumFile& infile);
		void        getGroupRhythms      (std::vector<std::string>& rhythms,
		                                  std::vector<HumNum>& durs,
		                                  std::vector<int>& states, HumdrumFile& infile);
		bool        hasGroupInterpretations(HumdrumFile& infile);
		void        checkForTremoloReduction(HumdrumFile& infile, int line, int field);
		void        reduceTremolos       (HumdrumFile& infile);
		bool        areAllEqual          (std::vector<HTp>& notes);
		void        getBeamedNotes       (std::vector<HTp>& notes, HTp starting);
		void        getPitches           (std::vector<int>& pitches, HTp token);
		void        addLabelsAndStria    (HumdrumFile& infile);
		void        addLabels            (HTp sstart, int labelIndex, const std::string& label,
		                                  int abbrIndex, const std::string& abbr);
		void        addStria             (HumdrumFile& infile, HTp spinestart);
		void        addVerseLabels       (HumdrumFile& infile, HTp spinestart);
		void        addVerseLabels2      (HumdrumFile& infile, HTp spinestart);
		bool        pitchesEqual         (std::vector<int>& pitches1, std::vector<int>& pitches2);
		void        mergeTremoloGroup    (std::vector<HTp>& notes, std::vector<int> groups, int group);
		bool        onlyAuxTremoloNotes  (HumdrumFile& infile, int line);
		void        removeAuxTremolosFromCompositeRhythm(HumdrumFile& infile);
		void        markTogether         (HumdrumFile& infile, int direction);
		void        markCoincidences     (HumdrumFile& infile, int direction);
		void        markCoincidencesMusic(HumdrumFile& infile);
		bool        isOnsetInBothGroups (HumdrumFile& infile, int line);
		void        extractNestingData   (HumdrumFile& infile);
		void        analyzeNestingDataGroups(HumdrumFile& infile, int direction);
		void        analyzeNestingDataAll(HumdrumFile& infile, int direction);
		void        getNestData          (HTp spine, int& total, int& coincide);
		void        getCoincidenceRhythms(std::vector<std::string>& rhythms, std::vector<int>& coincidences,
		                                  HumdrumFile& infile);
		void        fillInCoincidenceRhythm(std::vector<int>& coincidences,
		                                  HumdrumFile& infile, int direction);
		void        processCoincidenceInterpretation(HumdrumFile& infile, HTp token);
		bool        hasPipeRdf           (HumdrumFile& infile);
		void        extractGroup         (HumdrumFile& infile, const std::string &target);
		void        backfillGroup        (std::vector<std::vector<std::string>>& curgroup, HumdrumFile& infile,
		                                  int line, int track, int subtrack, const std::string& group);

		void        analyzeComposite      (HumdrumFile& infile);
		void        analyzeCompositeOnsets(HumdrumFile& infile, std::vector<HTp>& groups, std::vector<bool>& tracks);
		void        analyzeCompositeAccents(HumdrumFile& infile, std::vector<HTp>& groups, std::vector<bool>& tracks);
		void        analyzeCompositeOrnaments(HumdrumFile& infile, std::vector<HTp>& groups, std::vector<bool>& tracks);
		void        analyzeCompositeSlurs(HumdrumFile& infile, std::vector<HTp>& groups, std::vector<bool>& tracks);
		void        analyzeCompositeTotal(HumdrumFile& infile, std::vector<HTp>& groups, std::vector<bool>& tracks);

		void        getCompositeSpineStarts(std::vector<HTp>& groups, HumdrumFile& infile);
		std::vector<int> getExpansionList(std::vector<bool>& tracks, int maxtrack, int count);
		std::string makeExpansionString(std::vector<int>& tracks);
		void        doCoincidenceAnalysis(HumdrumFile& outfile, HumdrumFile& infile,
		                                  int ctrack, HTp compositeoldStart);
		void        doTotalAnalysis(HumdrumFile& outfile, HumdrumFile& infile, int ctrack);
		void        doGroupAnalyses(HumdrumFile& outfile, HumdrumFile& infile);
		int         countNoteOnsets(HTp token);
		void        doTotalOnsetAnalysis(std::vector<double>& analysis, HumdrumFile& infile,
		                                  int track, std::vector<bool>& tracks);
		void        doGroupOnsetAnalyses(std::vector<double>& analysisA,
		                                  std::vector<double>& analysisB,
		                                  HumdrumFile& infile);
		void        doCoincidenceOnsetAnalysis(std::vector<std::vector<double>>& analysis);
		void        insertAnalysesIntoFile(HumdrumFile& outfile, std::vector<std::string>& spines,
		                                   std::vector<int>& trackMap, std::vector<bool>& tracks);
		void        assignAnalysesToVdataTracks(std::vector<std::vector<double>*>& data,
		                                   std::vector<std::string>& spines, HumdrumFile& outfile);

	private:
		std::string m_pitch       = "eR";   // pitch to display for compositeold rhythm
		bool        m_onlygroupsQ = false;  // only split compositeold rhythms into markup groups
		bool        m_addgroupsQ  = false;  // do not split compositeold rhythms into markup groups
		bool        m_nogroupsQ   = false;  // has no groups in output
		bool        m_extractQ    = false;  // output only compositeold rhythm analysis (not input data)
		bool        m_appendQ     = false;  // display analysis at top of system
		bool        m_debugQ      = false;  // display debug information
		bool        m_graceQ      = false;  // include grace notes in compositeold rhythm
		bool        m_tremoloQ    = false;  // preserve tremolos
		bool        m_upQ         = false;  // force stem up
		bool        m_hasGroupsQ  = false;  // used with -M, -N option
		bool        m_nestQ       = false;  // used with --nest option
		bool        m_onlyQ       = false;  // used with --only option
		std::string m_only;                 // used with --only option
		bool        m_coincidenceQ = false; // used with -c option
		bool        m_assignedGroups = false;
		bool        m_suppressCMarkQ = false; // used with -c option when -M -m -N and -n not present
		std::string m_togetherInScore;    // used with -n option
		std::string m_together;           // used with -m option
		bool        m_coincideDisplayQ = true; // used with m_together and m_togetherInScore

		// Analysis variables:
		bool        m_analysisOnsetsQ    = false;   // used with -P option
		bool        m_analysisAccentsQ   = false;   // used with -A option
		bool        m_analysisOrnamentsQ = false;   // used with -O option
		bool        m_analysisSlursQ     = false;   // used with -S option
		bool        m_analysisTotalQ    = false;   // used with -T option
		bool        m_analysisQ          = false;   // union of -paost options
		bool        m_nozerosQ           = false;   // used with -Z option
		std::vector<std::vector<double>> m_analysisOnsets;    // used with -P
		std::vector<std::vector<double>> m_analysisAccents;   // used with -A
		std::vector<std::vector<double>> m_analysisOrnaments; // used with -O
		std::vector<std::vector<double>> m_analysisSlurs;     // used with -S
		std::vector<std::vector<double>> m_analysisTotal;    // used with -T

};


class Tool_deg : public HumTool {

	///////////////////////////////////////////////////////////////////
	//
	// Tool_deg::ScaleDegree --
	//

	public: // Tool_deg class
		class ScaleDegree;
		class ScaleDegree {
			public:  // ScaleDegree class
				ScaleDegree (void);
				~ScaleDegree ();

				void            setLinkedKernToken       (hum::HTp token, const std::string& mode, int b40tonic, bool unpitched = false);
				hum::HTp        getLinkedKernToken       (void) const;
				std::string     getDegToken              (void) const;

				hum::HumNum     getTimestamp             (void) const;
				hum::HumNum     getDuration              (void) const;
				hum::HumNum     getTiedDuration          (void) const;
				bool            hasSpines                (void) const;
				bool            isBarline                (void) const;
				std::string     getBarline               (void) const;
				bool            isExclusiveInterpretation(void) const;
				bool            isManipulator            (void) const;
				std::string     getManipulator           (void) const;
				bool            isInterpretation         (void) const;
				bool            isKeyDesignation         (void) const;
				bool            isLocalComment           (void) const;
				bool            isGlobalComment          (void) const;
				bool            isReferenceRecord        (void) const;
				bool            isUnpitched              (void) const;
				bool            isDataToken              (void) const;
				bool            isNullDataToken          (void) const;
				bool            isNonNullDataToken       (void) const;
				bool            isInMajorMode            (void) const;
				bool            isInMinorMode            (void) const;
				int             getBase40Tonic           (void) const;
				int             getSubtokenCount         (void) const;

				// output options:
				static void     setShowTies    (bool state) { m_showTiesQ = state;  }
				static void     setShowZeros   (bool state) { m_showZerosQ = state; }
				static void     setShowOctaves (bool state) { m_octaveQ = state; }
				static void     setForcedKey   (const std::string& key) { m_forcedKey = key; }

			protected:  // ScaleDegree class
				std::string     generateDegDataToken     (void) const;
				std::string     generateDegDataSubtoken  (int index) const;
				void            analyzeTokenScaleDegrees (void);

				void            setMajorMode             (int b40tonic);
				void            setMinorMode             (int b40tonic);
				void            setDorianMode            (int b40tonic);
				void            setPhrygianMode          (int b40tonic);
				void            setLydianMode            (int b40tonic);
				void            setMixolydianMode        (int b40tonic);
				void            setAeoleanMode           (int b40tonic);
				void            setLocrianMode           (int b40tonic);
				void            setIonianMode            (int b40tonic);

			private:  // ScaleDegree class
				// m_token: token in **kern data that links to this scale degree
				HTp m_linkedKernToken = NULL;

				// m_unpitched: true if unpitched (because in a percussion part)
				bool m_unpitched = false;

				// m_mode: the mode of the current key	(0 = none, 1 = major, 2 = minor)
				//
				// modal keys:
				// 3 = dorian (such as *c:dor)
				// 4 = phrygian (such as *c:phr)
				// 5 = lydian (such as *C:lyd)
				// 6 = mixolydian (such as *C:mix)
				// 7 = aeolean (such as *c:aeo)
				// 8 = locrian (such as *c:loc)
				// 9 = ionian (such as *C:ion)
				//
				int m_mode = 0;
				const int m_unknown_mode = 0;
				const int m_major_mode   = 1;
				const int m_minor_mode   = 2;
				const int m_dor_mode     = 3;
				const int m_phr_mode     = 4;
				const int m_lyd_mode     = 5;
				const int m_mix_mode     = 6;
				const int m_aeo_mode     = 7;
				const int m_loc_mode     = 8;
				const int m_ion_mode     = 9;

				// m_b40tonic: the tonic pitch of the key expressed as base-40
				int m_b40tonic = 0;

				// m_subtokens: Subtokens (of a chord)
				std::vector<std::string> m_subtokens;

				// m_degress: integer for scale degree (by subtoken)
				// 0 = rest; otherwise 1-7
				std::vector<int> m_degrees;

				// m_alters: chromatic alterations for scale degree
				std::vector<int> m_alters;

				// m_octaves: the octave number of the note
				// -1 = rest
				// 0-9 pitch octave (4 = middle C octave)
				std::vector<int> m_octaves;

				// Pointers to the next previous note (or chord) with which
				// to calculate a melodic contour approach or departure.
				ScaleDegree* m_prevNote = NULL;
				ScaleDegree* m_nextNote = NULL;

				// Pointers to the next/previous rest if there is a rest
				// between this note/chord and the next/previous note.
				// The pointer starts to the first rest if there is more
				// than one rest between the two notes.
				ScaleDegree* m_prevRest = NULL;
				ScaleDegree* m_nextRest = NULL;

				// ScaleDegree rendering options:
				static bool m_showTiesQ;
				static bool m_showZerosQ;
				static bool m_octaveQ;
				static std::string m_forcedKey;
		};


	/////////////////////////////////////////////////////////////////////////
	//
	// Tool_deg --
	//

	public:  // Tool_deg class
		      Tool_deg         (void);
		     ~Tool_deg         () {};

		bool  run              (HumdrumFileSet& infiles);
		bool  run              (HumdrumFile& infile);
		bool  run              (const std::string& indata, std::ostream& out);
		bool  run              (HumdrumFile& infile, std::ostream& out);

	protected: // Tool_deg class
		void            processFile              (HumdrumFile& infile);
		void            initialize               (void);

		bool            setupSpineInfo           (HumdrumFile& infile);
		void            prepareDegSpine          (std::vector<std::vector<ScaleDegree>>& degspine, HTp kernstart, HumdrumFile& infil);
		void            printDegScore            (HumdrumFile& infile);
		void            printDegScoreInterleavedWithInputScore(HumdrumFile& infile);
		std::string     createOutputHumdrumLine  (HumdrumFile& infile, int lineIndex);
      std::string     prepareMergerLine        (std::vector<std::vector<std::string>>& merge);
		void            calculateManipulatorOutputForSpine(std::vector<std::string>& lineout, std::vector<std::string>& linein);
		std::string     createRecipInterpretation(const std::string& starttok, int refLine);
		std::string     createDegInterpretation  (const std::string& degtok, int refLine, bool addPreSpine);
		std::string     printDegInterpretation   (const std::string& interp, HumdrumFile& infile, int lineIndex);
		void            getModeAndTonic          (std::string& mode, int& b40tonic, const std::string& token);

		bool            isDegAboveLine           (HumdrumFile& infile, int lineIndex);
		bool            isDegArrowLine           (HumdrumFile& infile, int lineIndex);
		bool            isDegBoxLine             (HumdrumFile& infile, int lineIndex);
		bool            isDegCircleLine          (HumdrumFile& infile, int lineIndex);
		bool            isDegColorLine           (HumdrumFile& infile, int lineIndex);
		bool            isDegHatLine             (HumdrumFile& infile, int lineIndex);
		bool            isDegSolfegeLine         (HumdrumFile& infile, int lineIndex);
		bool            isKeyDesignationLine     (HumdrumFile& infile, int lineIndex);

		void            checkAboveStatus         (std::string& value, bool arrowStatus);
		void            checkArrowStatus         (std::string& value, bool arrowStatus);
		void            checkBoxStatus           (std::string& value, bool arrowStatus);
		void            checkCircleStatus        (std::string& value, bool arrowStatus);
		void            checkColorStatus         (std::string& value, bool arrowStatus);
		void            checkHatStatus           (std::string& value, bool arrowStatus);
		void            checkSolfegeStatus       (std::string& value, bool arrowStatus);

		void            checkKeyDesignationStatus(std::string& value, int keyDesignationStatus);

	private: // Tool_deg class

		// m_degSpine: A three-dimensional list of **deg output spines.
		// This is a scratch pad to create **deg data for the input **kern
		//    spines.
		// First dimension is **kern spine enumeration in the input data,
		//    from left-to-right.
		// Second dimension is for the line in the Humdrum file, from top
		//    to bottom.
		// Third dimension is for the subspines (not subtokens, which are
		//    handled by Tool_deg::ScaleDegree class).
		std::vector<std::vector<std::vector<ScaleDegree>>> m_degSpines;

		// m_kernSpines: list of all **kern spines found in file.
		std::vector<HTp> m_kernSpines;

		// m_selectedKernSpines: list of only the **kern spines that will be analyzed.
		std::vector<HTp> m_selectedKernSpines;

		// m_degInsertTrack: the track number in the input file that an
		//	output **deg spine should be inserted before.  A track of -1 means
		// append the **deg spine after the last input spine.
		std::vector<int> m_degInsertTrack;

		// m_insertTracks: matches to m_degSpines first dimension.
		// It gives the track number for spines before which the corresponding
		// m_degSpine[x] spine should be inserted.  A -1 value at the last
		// position in m_insertTracks means append the **deg spine at the
		// end of the line.
		std::vector<int> m_insertTracks;

		bool m_aboveQ          = false;   // used with --above option
		bool m_arrowQ          = false;   // used with --arrow option
		bool m_boxQ            = false;   // used with --box option
		bool m_circleQ         = false;   // used with --circle option
		bool m_hatQ            = false;   // used with --hat option
		bool m_colorQ          = false;   // used with --color option
		std::string  m_color;             // used with --color option
		bool m_solfegeQ        = false;   // used with --solfege option

		bool m_degOnlyQ        = false;   // used with -I option
		bool m_recipQ          = false;   // used with -r option
		bool m_kernQ           = false;   // used with --kern option
		bool m_degTiesQ        = false;   // used with -t option
		bool m_forceKeyQ       = false;   // used with -K option

		std::string m_defaultKey  = "";    // used with --default-key option
		std::string m_forcedKey   = "";    // used with --forced-key option
		std::string m_kernSuffix  = "dR/"; // used with --kern option (currently hardwired)
		std::string m_spineTracks = "";    // used with -s option
		std::string m_kernTracks  = "";    // used with -k option

		std::vector<bool> m_processTrack;  // used with -k and -s option

		class InterleavedPrintVariables {
			public:
				bool foundData;
				bool hasDegSpines;
				bool foundAboveLine;
				bool foundArrowLine;
				bool foundBoxLine;
				bool foundCircleLine;
				bool foundColorLine;
				bool foundHatLine;
				bool foundKeyDesignationLine;
				bool foundSolfegeLine;

				InterleavedPrintVariables(void) { clear(); }
				void clear(void) {
					foundData       = false;
					hasDegSpines    = true;
					foundAboveLine  = false;
					foundArrowLine  = false;
					foundBoxLine    = false;
					foundCircleLine = false;
					foundColorLine  = false;
					foundHatLine    = false;
					foundKeyDesignationLine = false;
					foundSolfegeLine = false;
				}
		};
		InterleavedPrintVariables m_ipv;

};

std::ostream& operator<<(std::ostream& out, Tool_deg::ScaleDegree& degree);
std::ostream& operator<<(std::ostream& out, Tool_deg::ScaleDegree* degree);



class Tool_dissonant : public HumTool {
	public:
		         Tool_dissonant    (void);
		        ~Tool_dissonant    () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const string& indata, ostream& out);
		bool     run               (HumdrumFile& infile, ostream& out);

	protected:
		void    doAnalysis         (vector<vector<string> >& results,
		                            NoteGrid& grid,
		                            vector<vector<NoteCell*> >& attacks,
		                            bool debug);
		void    doAnalysisForVoice (vector<vector<string> >& results,
		                            NoteGrid& grid,
		                            vector<NoteCell*>& attacks,
		                            int vindex, bool debug);
		void    findFakeSuspensions(vector<vector<string> >& results,
		                            NoteGrid& grid,
		                            vector<NoteCell*>& attacks, int vindex);
		void    findAppoggiaturas  (vector<vector<string> >& results,
		                            NoteGrid& grid,
		                            vector<NoteCell*>& attacks, int vindex);
		void    findLs             (vector<vector<string> >& results,
		                            NoteGrid& grid,
		                            vector<NoteCell*>& attacks, int vindex);
		void    findYs             (vector<vector<string> >& results,
		                            NoteGrid& grid,
		                            vector<NoteCell*>& attacks, int vindex);
		void    findCadentialVoiceFunctions(vector<vector<string> >& results,
		                            NoteGrid& grid, vector<NoteCell*>& attacks,
		                            vector<vector<string> >& voiceFuncs,
		                            int vindex);

		void    printColorLegend   (HumdrumFile& infile);
		int     getNextPitchAttackIndex(NoteGrid& grid, int voicei,
		                            int sliceindex);
		void    fillLabels         (void);
		void    fillLabels2        (void);
		void    printCountAnalysis (vector<vector<string> >& data);
		void    suppressDissonances(HumdrumFile& infile, NoteGrid& grid,
		                            vector<vector<NoteCell* > >& attacks,
		                            vector<vector<string> >& results);
		void    suppressDissonancesInVoice(HumdrumFile& infile,
		                            NoteGrid& grid, int vindex,
		                            vector<NoteCell*>& attacks,
		                            vector<string>& results);
		void    suppressSusOrnamentsInVoice(HumdrumFile& infile,
		                            NoteGrid& grid, int vindex,
		                            vector<NoteCell*>& attacks,
		                            vector<string>& results);
		void    mergeWithPreviousNote(HumdrumFile& infile, int line, int field);
		void    mergeWithNextNote(HumdrumFile& infile, int line, int field);
		void    changeDurationOfNote(HTp note, HumNum dur);
		void    changePitch        (HTp note2, HTp note1);
		void    simplePreviousMerge(HTp pnote, HTp cnote);
		void    simpleNextMerge    (HTp cnote, HTp nnote);
		void    changePitchOfTieGroupFollowing(HTp note, const string& pitch);
		void    mergeWithPreviousNoteViaTies(HTp pnote, HTp cnote);
		void    mergeWithPreviousNote(HumdrumFile& infile, NoteCell* cell);
		void    mergeWithNextNote    (HumdrumFile& infile, NoteCell* cell);
		void    adjustColorization   (HumdrumFile& infile);
		void    adjustColorForVoice  (HTp spinestart, vector<string>& labels);
		void    removeAgentColor     (HTp disslabel, const string& marker, const string& query);
		void    addLabelToSuspensions(HTp disslabel, const string& marker);
		bool    isSuspension         (HTp token);
		void    addSuspensionMarkToNote(HTp start, const string& marks);
		void    adjustSuspensionColors(HTp speinstart);

	private:
		vector<HTp> m_kernspines;
		bool diss2Q = false;
		bool diss7Q = false;
		bool diss4Q = false;
		bool dissL0Q = false;
		bool dissL1Q = false;
		bool dissL2Q = false;
		bool suppressQ = false;
		bool voiceFuncsQ = false;
		bool m_voicenumQ = false;
		bool m_selfnumQ = false;

		vector<string> m_labels;

		// unaccdented non-harmonic tones:
		const int PASSING_UP           =  0; // rising passing tone
		const int PASSING_DOWN         =  1; // downward passing tone
		const int NEIGHBOR_UP          =  2; // upper neighbor
		const int NEIGHBOR_DOWN        =  3; // lower neighbor
		const int ECHAPPEE_UP          =  4; // upper échappée
		const int ECHAPPEE_DOWN        =  5; // lower échappée
		const int CAMBIATA_UP_S        =  6; // ascending short nota cambiata
		const int CAMBIATA_DOWN_S      =  7; // descending short nota cambiata
		const int CAMBIATA_UP_L        =  8; // ascending long nota cambiata
		const int CAMBIATA_DOWN_L      =  9; // descending long nota cambiata
		const int REV_CAMBIATA_UP      = 10; // incomplete anterior upper neighbor
		const int REV_CAMBIATA_DOWN    = 11; // incomplete anterior lower neighbor
		const int REV_ECHAPPEE_UP      = 12; // incomplete posterior upper neighbor
		const int REV_ECHAPPEE_DOWN    = 13; // incomplete posterior lower neighbor
		const int ANT_UP               = 14; // rising anticipation
		const int ANT_DOWN             = 15; // descending anticipation
		const int DBL_NEIGHBOR_UP      = 16; // double neighbor beginning with upper neighbor
		const int DBL_NEIGHBOR_DOWN    = 17; // double neighbor beginning with lower neighbor

		// accented non-harmonic tones:
		const int THIRD_Q_PASS_UP      = 18; // dissonant third quarter
		const int THIRD_Q_PASS_DOWN    = 19; // dissonant third quarter
		const int THIRD_Q_UPPER_NEI    = 20; // dissonant third quarter
		const int THIRD_Q_LOWER_NEI    = 21; // dissonant third quarter
		const int ACC_PASSING_UP       = 22; // appoggiatura
		const int ACC_PASSING_DOWN     = 23; // appoggiatura
		const int ACC_UP_NEI           = 24; // appoggiatura
		const int ACC_LO_NEI           = 25; // appoggiatura
		const int APP_UPPER            = 26; // appoggiatura
		const int APP_LOWER            = 27; // appoggiatura
		const int SUS_BIN              = 28; // binary suspension
		const int SUS_TERN             = 29; // ternary suspension
		const int AGENT_BIN            = 30; // binary agent
		const int AGENT_TERN           = 31; // ternary agent
		const int SUSPENSION_REP       = 32; // suspension repeated note
		const int FAKE_SUSPENSION_LEAP = 33; // fake suspension approached by leap
		const int FAKE_SUSPENSION_STEP = 34; // fake suspension approached by step or anticipation
		const int SUS_NO_AGENT_LEAP    = 35; // suspension missing a normal agent approached by leap
		const int SUS_NO_AGENT_STEP    = 36; // suspension missing a normal agent approached by step or anticipation
		const int CHANSON_IDIOM        = 37; // chanson idiom
		const int ORNAMENTAL_SUS       = 38; // purely ornamental suspension

		// unknown dissonances:
		const int PARALLEL_UP          = 39; // moves in parallel with known dissonant, approached from below
		const int PARALLEL_DOWN        = 40; // moves in parallel with known dissonant, approached from above
		const int RES_PITCH            = 41; // note of resolution of a suspension against suspension dissonance

		const int ONLY_WITH_VALID_UP   = 42; // only dissonant with identifiable dissonances, approached from below
		const int ONLY_WITH_VALID_DOWN = 43; // only dissonant with identifiable dissonances, approached from above
		const int UNKNOWN_DISSONANCE   = 44; // unknown dissonance type
		const int UNLABELED_Z2         = 45; // unknown dissonance type, 2nd interval
		const int UNLABELED_Z7         = 46; // unknown dissonance type, 7th interval
		const int UNLABELED_Z4         = 47; // unknown dissonance type, 4th interval

		const int LABELS_SIZE          = 48; // one more than last index
};


class Tool_double : public HumTool {
	public:
		         Tool_double     (void);
		        ~Tool_double     () {};

		bool     run                (HumdrumFileSet& infiles);
		bool     run                (HumdrumFile& infile);
		bool     run                (const std::string& indata, std::ostream& out);
		bool     run                (HumdrumFile& infile, std::ostream& out);

	protected:
		void     initialize         (HumdrumFile& infile);
		void     processFile        (HumdrumFile& infile);
		void     doubleRhythms      (HumdrumFile& infile);
		void     terminalBreveToTerminalLong(HumdrumFile& infile);
		void     processBeamsForMeasure(std::vector<HTp>& notes);
		void     adjustBeams        (HumdrumFile& infile);
		void     adjustBeams        (HTp sstart, HTp send);

	private:

};


class Tool_esac2hum : public HumTool {
	public:

		class Note {
			public:
				std::vector<std::string> m_errors;
				std::string esac;
				int    m_dots        = 0;
				int    m_underscores = 0;
				int    m_octave      = 0;
				int    m_degree      = 0;  // scale degree (wrt major key)
				int    m_b40degree   = 0;  // scale degree as b40 interval
				int    m_alter       = 0;  // chromatic alteration of degree (flats/sharp from major scale degrees)
				double m_ticks       = 0.0;
				bool   m_tieBegin    = false;
				bool   m_tieEnd      = false;
				bool   m_phraseBegin = false;
				bool   m_phraseEnd   = false;
				std::string m_humdrum; // **kern conversion of EsAC note
				int    m_b40         = 0;  // absolute b40 pitch (-1000 = rest);
				int    m_b12         = 0;  // MIDI note number (-1000 = rest);
				HumNum m_factor      = 1;  // for triplet which is 2/3 duration

				void calculateRhythms(int minrhy);
				void calculatePitches(int tonic);
				bool parseNote(const std::string& note, HumNum factor);
				void generateHumdrum(int minrhy, int b40tonic);
				bool isPitch(void);
				bool isRest(void);
				std::string getScaleDegree(void);
		};

		class Measure : public std::vector<Tool_esac2hum::Note> {
			public:
				std::vector<std::string> m_errors;
				std::string esac;
				int m_barnum = -1000; // -1000 == unassigned bar number for this measure
				// m_barnum = -1 == invisible barline (between two partial measures)
				// m_barnum =  0 == pickup measure (partial measure at start of music)
				double m_ticks = 0.0;
				double m_tsticks = 0.0;
				// m_measureTimeSignature is a **kern time signature
				// (change) to display in the converted score.
				std::string m_measureTimeSignature = "";
				bool m_partialBegin = false;  // start of an incomplete measure
				bool m_partialEnd = false;    // end of an incomplete measure (pickup)
				bool m_complete = false;      // a complste measure
				void calculateRhythms(int minrhy);
				void calculatePitches(int tonic);
				bool parseMeasure(const std::string& measure);
				bool isUnassigned(void);
				void setComplete(void);
				bool isComplete(void);
				void setPartialBegin(void);
				bool isPartialBegin(void);
				void setPartialEnd(void);
				bool isPartialEnd(void);
		};

		class Phrase : public std::vector<Tool_esac2hum::Measure> {
			public:
				std::vector<std::string> m_errors;
				double m_ticks = 0.0;
				std::string esac;
				void calculateRhythms(int minrhy);
				void calculatePitches(int tonic);
				bool parsePhrase(const std::string& phrase);
				std::string getLastScaleDegree();
				void getNoteList(std::vector<Tool_esac2hum::Note*>& notelist);
				std::string getNO_REP(void);
				int getFullMeasureCount(void);
		};

		class Score : public std::vector<Tool_esac2hum::Phrase> {
			public:
				int m_b40tonic = 0;
				int m_minrhy   = 0;
				std::string m_clef;
				std::string m_keysignature;
				std::string m_keydesignation;
				std::string m_timesig;
				std::map<std::string, std::string> m_params;
				std::vector<std::string> m_errors;
				bool m_finalBarline = false;
				bool hasFinalBarline(void) { return m_finalBarline; }
				void calculateRhythms(int minrhy);
				void calculatePitches(int tonic);
				bool parseMel(const std::string& mel);
				void analyzeTies(void);
				void analyzePhrases(void);
				void getNoteList(std::vector<Tool_esac2hum::Note*>& notelist);
				void getMeasureList(std::vector<Tool_esac2hum::Measure*>& measurelist);
				void getPhraseNoteList(std::vector<Tool_esac2hum::Note*>& notelist, int index);
				void generateHumdrumNotes(void);
				void calculateClef(void);
				void calculateKeyInformation(void);
				void calculateTimeSignatures(void);
				void setAllTimesigTicks(double ticks);
				void assignFreeMeasureNumbers(void);
				void assignSingleMeasureNumbers(void);
				void prepareMultipleTimeSignatures(const std::string& ts);

				void doAnalyses(void);
				void analyzeMEL_SEM(void);
				void analyzeMEL_RAW(void);
				void analyzeNO_REP(void);
				void analyzeRTM(void);
				void analyzeSCL_DEG(void);
				void analyzeSCL_SEM(void);
				void analyzePHR_NO(void);
				void analyzePHR_BARS(void);
				void analyzePHR_CAD(void);
				void analyzeACC(void);
		};

		            Tool_esac2hum    (void);
		           ~Tool_esac2hum    () {};

		bool       convertFile          (std::ostream& out, const std::string& filename);
		bool       convert              (std::ostream& out, const std::string& input);
		bool       convert              (std::ostream& out, std::istream& input);


	protected:
		void        initialize          (void);

		void        convertEsacToHumdrum(std::ostream& output, std::istream& infile);
		bool        getSong             (std::vector<std::string>& song, std::istream& infile);
		void        convertSong         (std::ostream& output, std::vector<std::string>& infile);
		static std::string trimSpaces   (const std::string& input);
		void        printHeader         (std::ostream& output);
		void        printFooter         (std::ostream& output, std::vector<std::string>& infile);
		void        printConversionDate (std::ostream& output);
		void        printPdfLinks       (std::ostream& output);
		void        printParameters     (void);
		void        printPageNumbers    (std::ostream& output);
		void        getParameters       (std::vector<std::string>& infile);
		void        cleanText           (std::string& buffer);
		std::string createFilename      (void);
		void        printBemComment     (std::ostream& output);
		void        processSong         (void);
		void        printScoreContents  (std::ostream& output);
		void        embedAnalyses       (std::ostream& output);
		void        printPdfUrl         (std::ostream& output);
		std::string getKolbergUrl       (int volume);
      void        printKolbergPdfUrl  (std::ostream& output);

	private:
		bool        m_debugQ     = false;  // used with --debug option
		bool        m_verboseQ   = false;  // used with --verbose option
		std::string m_verbose;             //    p = print EsAC phrases, m = print measures, n = print notes.
		                                   //    t after p, m, or n means print tick info
		bool        m_embedEsacQ = true;   // used with -E option
		bool        m_dwokQ      = false;  // true if source is Oskar Kolberg: Dzieła Wszystkie
		                                   // (Oskar Kolberg: Complete Works)
		                                   // determined automatically if header line or TRD source contains "DWOK" string.
		bool        m_analysisQ  = false;  // used with -a option

		int         m_inputline = 0;       // used to keep track if the EsAC input line.

		std::string m_filePrefix;
		std::string m_filePostfix = ".krn";
		bool m_fileTitleQ = false;

		std::string m_prevline;
		std::string m_cutline;
		std::vector<std::string> m_globalComments;

		bool m_initialized = false;
		int m_minrhy = 0;

		Tool_esac2hum::Score m_score;

		class KolbergInfo {
			public:
				std::string titlePL;
				std::string titleEN;
				int firstPrintPage;
				int firstScanPage;
				std::vector<int> plates;

				KolbergInfo(void) { firstPrintPage = 0; firstScanPage = 0; }
				KolbergInfo(
					const std::string& pl, const std::string& en, int fpp, int fsp, const std::vector<int>& plts)
        				: titlePL(pl), titleEN(en), firstPrintPage(fpp), firstScanPage(fsp), plates(plts) {}
		};
		std::map<int, KolbergInfo> m_kinfo;
		KolbergInfo getKolbergInfo(int volume);
		std::string getKolbergUrl(int volume, int printPage);
		int calculateScanPage(int inputPrintPage, int printPage, int scanPage, const std::vector<int>& platePages);


};



#define ND_NOTE 0  /* notes or rests + text and phrase markings */
#define ND_BAR  1  /* explicit barlines */


class NoteData {
	public:
		NoteData(void) { clear(); }
		void clear(void) { bar = pitch = phstart = phend = 0;
							  phnum = -1;
							  lyricerr = lyricnum = 0;
							  tiestart = tiecont = tieend = 0;
							  slstart = slend = 0;
							  num = denom = barnum = 0;
							  barinterp = 0; bardur = 0.0;
							  duration = 0.0; text = ""; }
		double duration;
		int    bar;       int    num;
		int    denom;     int    barnum;
		double bardur;    int    barinterp;
		int    pitch;     int    lyricerr;
		int    phstart;   int    phend;    int phnum;
		int    slstart;   int    slend;    int lyricnum;
		int    tiestart;  int    tiecont;  int tieend;
		std::string text;
};



class Tool_esac2humold : public HumTool {
	public:
		        Tool_esac2humold    (void);
		       ~Tool_esac2humold    () {};

		bool    convertFile          (std::ostream& out, const std::string& filename);
		bool    convert              (std::ostream& out, const std::string& input);
		bool    convert              (std::ostream& out, std::istream& input);

	protected:
		bool      initialize            (void);
		void      checkOptions          (Options& opts, int argc, char** argv);
		void      example               (void);
		void      usage                 (const std::string& command);
		void      convertEsacToHumdrum  (std::ostream& out, std::istream& input);
		bool      getSong               (std::vector<std::string>& song, std::istream& infile,
		                                int init);
		void      convertSong           (std::vector<std::string>& song, std::ostream& out);
		bool      getKeyInfo            (std::vector<std::string>& song, std::string& key,
		                                 double& mindur, int& tonic, std::string& meter,
		                                 std::ostream& out);
		void      printNoteData         (NoteData& data, int textQ, std::ostream& out);
		bool      getNoteList           (std::vector<std::string>& song,
		                                 std::vector<NoteData>& songdata, double mindur,
		                                 int tonic);
		void      getMeterInfo          (std::string& meter, std::vector<int>& numerator,
		                                 std::vector<int>& denominator);
		void      postProcessSongData   (std::vector<NoteData>& songdata,
		                                 std::vector<int>& numerator,std::vector<int>& denominator);
		void      printKeyInfo          (std::vector<NoteData>& songdata, int tonic,
		                                 int textQ, std::ostream& out);
		int       getAccidentalMax      (int a, int b, int c);
		bool      printTitleInfo        (std::vector<std::string>& song, std::ostream& out);
		void      getLineRange          (std::vector<std::string>& song, const std::string& field,
		                                 int& start, int& stop);
		void      printChar             (unsigned char c, std::ostream& out);
		void      printBibInfo          (std::vector<std::string>& song, std::ostream& out);
		void      printString           (const std::string& string, std::ostream& out);
		void      printSpecialChars     (std::ostream& out);
		bool      placeLyrics           (std::vector<std::string>& song,
		                                 std::vector<NoteData>& songdata);
		bool      placeLyricPhrase      (std::vector<NoteData>& songdata,
		                                 std::vector<std::string>& lyrics, int line);
		void      getLyrics             (std::vector<std::string>& lyrics, const std::string& buffer);
		void      cleanupLyrics         (std::vector<std::string>& lyrics);
		bool      getFileContents       (std::vector<std::string>& array, const std::string& filename);
		void      chopExtraInfo         (std::string& buffer);
		void      printHumdrumHeaderInfo(std::ostream& out, std::vector<std::string>& song);
		void      printHumdrumFooterInfo(std::ostream& out, std::vector<std::string>& song);

	private:
		int            debugQ = 0;         // used with --debug option
		int            verboseQ = 0;       // used with -v option
		int            splitQ = 0;         // used with -s option
		int            firstfilenum = 1;   // used with -f option
		std::vector<std::string> header;   // used with -h option
		std::vector<std::string> trailer;  // used with -t option
		std::string         fileextension; // used with -x option
		std::string         namebase;      // used with -s option

		// Modern ESaC files use UTF-8 characters, older ESaC files use
		//  ASCII encodings of non-UTF7 characters:
		std::vector<int>    chartable;  // used in printChars() & printSpecialChars()
		int inputline = 0;

};


class Tool_extract : public HumTool {
	public:
		         Tool_extract           (void);
		        ~Tool_extract           () {};

		bool     run                    (HumdrumFileSet& infiles);
		bool     run                    (HumdrumFile& infile);
		bool     run                    (const std::string& indata, std::ostream& out);
		bool     run                    (HumdrumFile& infile, std::ostream& out);

	protected:

		// auto transpose functions:
		void     initialize             (HumdrumFile& infile);

		// function declarations
		void    processFile             (HumdrumFile& infile);
		void    excludeFields           (HumdrumFile& infile, std::vector<int>& field,
		                                 std::vector<int>& subfield, std::vector<int>& model);
		void    extractFields           (HumdrumFile& infile, std::vector<int>& field,
		                                 std::vector<int>& subfield, std::vector<int>& model);
		void    extractTrace            (HumdrumFile& infile, const std::string& tracefile);
		void    getInterpretationFields (std::vector<int>& field, std::vector<int>& subfield,
		                                 std::vector<int>& model, HumdrumFile& infile,
		                                 std::string& interps, int state);
		//void    extractInterpretations  (HumdrumFile& infile, std::string& interps);
		void    example                 (void);
		void    usage                   (const std::string& command);
		std::string reverseFieldString(const std::string& input, int maxval);
		void    fillFieldData           (std::vector<int>& field, std::vector<int>& subfield,
		                                 std::vector<int>& model, std::string& fieldstring,
		                                 HumdrumFile& infile);
		void    processFieldEntry       (std::vector<int>& field, std::vector<int>& subfield,
		                                 std::vector<int>& model, const std::string& astring,
		                                 HumdrumFile& infile);
		void    removeDollarsFromString (std::string& buffer, int maxtrack);
		int     isInList                (int number, std::vector<int>& listofnum);
		void    getTraceData            (std::vector<int>& startline,
		                                 std::vector<std::vector<int> >& fields,
		                                 const std::string& tracefile, HumdrumFile& infile);
		void    printTraceLine          (HumdrumFile& infile, int line,
		                                 std::vector<int>& field);
		void    dealWithSpineManipulators(HumdrumFile& infile, int line,
		                                 std::vector<int>& field, std::vector<int>& subfield,
		                                 std::vector<int>& model);
		void    storeToken              (std::vector<std::string>& storage,
		                                 const std::string& string);
		void    storeToken              (std::vector<std::string>& storage, int index,
		                                 const std::string& string);
		void    printMultiLines         (std::vector<int>& vsplit, std::vector<int>& vserial,
		                                 std::vector<std::string>& tempout);
		void    reverseSpines           (std::vector<int>& field, std::vector<int>& subfield,
		                                 std::vector<int>& model, HumdrumFile& infile,
		                                 const std::string& exinterp);
		void    getSearchPat            (std::string& spat, int target,
		                                 const std::string& modifier);
		void    expandSpines            (std::vector<int>& field, std::vector<int>& subfield,
		                                 std::vector<int>& model, HumdrumFile& infile,
		                                 std::string& interp);
		void    dealWithSecondarySubspine(std::vector<int>& field, std::vector<int>& subfield,
		                                 std::vector<int>& model, int targetindex,
		                                 HumdrumFile& infile, int line, int spine,
		                                 int submodel);
		void    dealWithCospine         (std::vector<int>& field, std::vector<int>& subfield,
		                                 std::vector<int>& model, int targetindex,
		                                 HumdrumFile& infile, int line, int cospine,
		                                 int comodel, int submodel,
		                                 const std::string& cointerp);
		void    printCotokenInfo        (int& start, HumdrumFile& infile, int line,
		                                 int spine, std::vector<std::string>& cotokens,
		                                 std::vector<int>& spineindex,
		                                 std::vector<int>& subspineindex);
		void    fillFieldDataByGrep     (std::vector<int>& field, std::vector<int>& subfield,
		                                 std::vector<int>& model, const std::string& grepString,
		                                 HumdrumFile& infile, int state);
		std::vector<int> getNullDataTracks(HumdrumFile& infile);
		void fillFieldDataByEmpty       (std::vector<int>& field, std::vector<int>& subfield,
				                           std::vector<int>& model, HumdrumFile& infile, int negate);
		void fillFieldDataByNoEmpty     (std::vector<int>& field, std::vector<int>& subfield,
				                           std::vector<int>& model, HumdrumFile& infile, int negate);
		void fillFieldDataByNoRest      (std::vector<int>& field, std::vector<int>& subfield,
		                                 std::vector<int>& model, const std::string& searchstring,
		                                 HumdrumFile& infile, int state);
		void printInterpretationForKernSpine(HumdrumFile& infile, int index);

	private:

		// global variables
		bool        excludeQ     = false;     // used with -x option
		bool        expandQ      = false;     // used with -e option
		std::string expandInterp = "";        // used with -E option
		bool        interpQ      = false;     // used with -i option
		std::string interps      = "";        // used with -i option
		bool        debugQ       = false;     // used with --debug option
		bool        kernQ        = false;     // used with -k option
		bool        rkernQ       = false;     // used with -K option
		bool        fieldQ       = false;     // used with -f or -p option
		std::string fieldstring  = "";        // used with -f or -p option
		std::vector<int> field;               // used with -f or -p option
		std::vector<int> subfield;            // used with -f or -p option
		std::vector<int> model;               // used with -p, or -e options and similar
		bool        countQ        = false;    // used with -C option
		bool        traceQ        = false;    // used with -t option
		std::string tracefile     = "";       // used with -t option
		bool        reverseQ      = false;    // used with -r option
		std::string reverseInterp = "**kern"; // used with -r and -R options.
		// sub-spine "b" expansion model: how to generate data for a secondary
		// spine if the primary spine is not divided.  Models are:
		//    'd': duplicate primary spine (or "a" subspine) data (default)
		//    'n': null = use a null token
		//    'r': rest = use a rest instead of a primary spine note (in **kern)
		//         data.  'n' will be used for non-kern spines when 'r' is used.
		int          submodel = 'd';       // used with -m option
		std::string editorialInterpretation = "yy";
		std::string cointerp    = "**kern";  // used with -c option
		int         comodel     = 0;         // used with -M option
		std::string subtokenseparator = " "; // used with a future option
		int         interpstate = 0;         // used -I or with -i
		bool        grepQ       = false;     // used with -g option
		std::string grepString  = "";        // used with -g option
		std::string blankName   = "**blank"; // used with -n option
 		bool        addRestsQ   = false;     // used with -n option
		bool        noEmptyQ    = false;     // used with --no-empty option
		bool        emptyQ      = false;     // used with --empty option
		bool        spineListQ  = false;     // used with --spine option
		bool        removerestQ = false;     // used with --no-rest option

};



class FiguredBassNumber {
	public:
		            FiguredBassNumber(int num, string accid, bool showAccid, int voiceIndex, int lineIndex, bool isAttack, bool intervallsatz, string intervalQuality, bool hint);
		std::string toString(bool nonCompoundIntervalsQ, bool noAccidentalsQ, bool hideThreeQ);
		int         getNumberWithinOctave(void);

		int         m_voiceIndex;
		int         m_lineIndex;
		int         m_number;
		std::string m_accidentals;
		bool        m_showAccidentals; // Force shoing figured base numbers when they need an accidental
		bool        m_baseOfSustainedNoteDidChange;
		bool        m_isAttack;
		bool        m_convert2To9 = false;
		bool        m_intervallsatz = false;
		std::string m_intervalQuality;
		bool        m_hint = false;

};

class FiguredBassAbbreviationMapping {
	public:
		FiguredBassAbbreviationMapping(string s, vector<int> n);

		const static vector<FiguredBassAbbreviationMapping> s_mappings;

		// String to compare the numbers with
		// e.g. "6 4 3"
		// Sorted by size, larger numbers first
		string m_str;

		// Figured bass number as int
		vector<int> m_numbers;

};

class Tool_fb : public HumTool {

	public:
		     Tool_fb (void);
		     ~Tool_fb() {};

		bool run     (HumdrumFileSet& infiles);
		bool run     (HumdrumFile& infile);
		bool run     (const string& indata, ostream& out);
		bool run     (HumdrumFile& infile, ostream& out);

	protected:
		void                       initialize                             (void);
        void                       processFile                            (HumdrumFile& infile);
		bool                       hideNumbersForTokenLine                (HTp token, pair<int, HumNum> timeSig);
		vector<string>             getTrackData                           (const vector<FiguredBassNumber*>& numbers, int lineCount);
		vector<string>             getTrackDataForVoice                   (int voiceIndex, const vector<FiguredBassNumber*>& numbers, int lineCount);
		FiguredBassNumber*         createFiguredBassNumber                (int basePitchBase40, int targetPitchBase40, int voiceIndex, int lineIndex, bool isAttack, string keySignature);
		vector<FiguredBassNumber*> filterNegativeNumbers                  (vector<FiguredBassNumber*> numbers);
		vector<FiguredBassNumber*> filterFiguredBassNumbersForLine        (vector<FiguredBassNumber*> numbers, int lineIndex);
		vector<FiguredBassNumber*> filterFiguredBassNumbersForLineAndVoice(vector<FiguredBassNumber*> numbers, int lineIndex, int voiceIndex);
		string                     formatFiguredBassNumbers               (const vector<FiguredBassNumber*>& numbers);
		vector<FiguredBassNumber*> analyzeChordNumbers                    (const vector<FiguredBassNumber*>& numbers);
		vector<FiguredBassNumber*> getAbbreviatedNumbers                  (const vector<FiguredBassNumber*>& numbers);
		string                     getNumberString                        (vector<FiguredBassNumber*> numbers);
		string                     getKeySignature                        (HumdrumFile& infile, int lineIndex);
		int                        getLowestBase40Pitch                   (vector<int> base40Pitches);
		string                     getIntervalQuality                     (int basePitchBase40, int targetPitchBase40);


	private:
		bool   m_compoundQ      = false;
		bool   m_accidentalsQ   = false;
		int    m_baseTrackQ     = 1;
		bool   m_intervallsatzQ = false;
		bool   m_sortQ          = false;
		bool   m_lowestQ        = false;
		bool   m_normalizeQ     = false;
		bool   m_reduceQ        = false;
		bool   m_attackQ        = false;
		bool   m_figuredbassQ   = false;
		bool   m_hideThreeQ     = false;
		bool   m_showNegativeQ  = false;
		bool   m_aboveQ         = false;
		string m_rateQ          = "";
		bool   m_hintQ          = false;

		string m_spineTracks    = ""; // used with -s option
		string m_kernTracks     = ""; // used with -k option
		vector<bool> m_selectedKernSpines;  // used with -k and -s option

};


class Tool_filter : public HumTool {
	public:
		         Tool_filter        (void);
		        ~Tool_filter        () {};

		bool     run                (HumdrumFileSet& infiles);
		bool     run                (HumdrumFile& infile);
		bool     run                (const std::string& indata);

		bool     runUniversal       (HumdrumFileSet& infiles);

	protected:
		void     getCommandList     (std::vector<std::pair<std::string, std::string> >& commands,
		                             HumdrumFile& infile);
		void     getUniversalCommandList(std::vector<std::pair<std::string, std::string> >& commands,
		                             HumdrumFileSet& infiles);
		void     initialize         (HumdrumFile& infile);
		void     removeGlobalFilterLines    (HumdrumFile& infile);
		void     removeUniversalFilterLines (HumdrumFileSet& infiles);
		void     splitPipeline      (std::vector<std::string>& clist, const std::string& command);

	private:
		std::string   m_variant;        // used with -v option.
		bool     m_debugQ = false; // used with --debug option

};


class Tool_fixps : public HumTool {
	public:
		         Tool_fixps         (void);
		        ~Tool_fixps         () {};

		bool     run                (HumdrumFileSet& infiles);
		bool     run                (HumdrumFile& infile);
		bool     run                (const std::string& indata, std::ostream& out);
		bool     run                (HumdrumFile& infile, std::ostream& out);

	protected:
		void     initialize         (HumdrumFile& infile);
		void     processFile        (HumdrumFile& infile);
		void     markEmptyVoices    (HumdrumFile& infile);
		void     removeEmpties      (std::vector<std::vector<HTp>>& newlist, HumdrumFile& infile);
		void     removeDuplicateDynamics(HumdrumFile& infile);
		void     outputNewSpining   (std::vector<std::vector<HTp>>& newlist, HumdrumFile& infile);
		void     printNewManipulator(HumdrumFile& infile, std::vector<std::vector<HTp>>& newlist, int line);

	private:

};


class Tool_flipper : public HumTool {
	public:
		         Tool_flipper      (void);
		        ~Tool_flipper      () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void     processFile       (HumdrumFile& infile);
		void     initialize        (void);

		void     processLine        (HumdrumFile& infile, int index);
		void     checkForFlipChanges(HumdrumFile& infile, int index);
		bool     flipSubspines      (std::vector<std::vector<HTp>>& flipees);
		void     flipSpineTokens    (std::vector<HTp>& subtokens);
		void     extractFlipees     (std::vector<std::vector<HTp>>& flipees,
		                             HumdrumFile& infile, int index);

	private:
		bool     m_allQ         = false;
		bool     m_keepQ        = false;
		bool     m_kernQ        = false;
		bool     m_stropheQ     = false;
		std::string m_interp;
		std::vector<bool> m_flipState;
		std::vector<bool> m_fliplines;
		std::vector<bool> m_strophe;

};


class Tool_gasparize : public HumTool {
	public:
		         Tool_gasparize     (void);
		        ~Tool_gasparize     () {};

		bool     run                (HumdrumFileSet& infiles);
		bool     run                (HumdrumFile& infile);
		bool     run                (const std::string& indata, std::ostream& out);
		bool     run                (HumdrumFile& infile, std::ostream& out);

	protected:
		void     initialize         (HumdrumFile& infile);
		void     processFile        (HumdrumFile& infile);
		void     checkDataLine      (HumdrumFile& infile, int lineindex);
		void     addBibliographicRecords(HumdrumFile& infile);
		void     fixEditorialAccidentals(HumdrumFile& infile);
		void     fixInstrumentAbbreviations(HumdrumFile& infile);
		void     addTerminalLongs   (HumdrumFile& infile);
		void     deleteDummyTranspositions(HumdrumFile& infile);
		std::string   getDate            (void);
		void     adjustSystemDecoration(HumdrumFile& infile);
		void     deleteBreaks       (HumdrumFile& infile);
		void     updateKeySignatures(HumdrumFile& infile, int lineindex);
		void     convertBreaks      (HumdrumFile& infile);
		void     clearStates        (void);
		void     removeArticulations(HumdrumFile& infile);
		void     fixTies            (HumdrumFile& infile);
		void     fixTiesForStrand   (HTp sstart, HTp send);
		void     fixTieToInvisibleRest(HTp first, HTp second);
		void     fixHangingTie      (HTp first, HTp second);
		void     addMensurations    (HumdrumFile& infile);
		void     addMensuration     (int top, HumdrumFile& infile, int i);
		void     createEditText     (HumdrumFile& infile);
		bool     addEditStylingForText(HumdrumFile& infile, HTp sstart, HTp send);
		std::string   getEditLine        (const std::string& text, int fieldindex, HLp line);
		bool     insertEditText     (const std::string& text, HumdrumFile& infile, int line, int field);
		void     adjustIntrumentNames(HumdrumFile& infile);
		void     removeKeyDesignations(HumdrumFile& infile);
		void     fixBarlines        (HumdrumFile& infile);
		void     fixFinalBarline    (HumdrumFile& infile);
		void     removeDoubledAccidentals(HumdrumFile& infile);
		void     createJEditorialAccidentals(HumdrumFile& infile);
		void     createJEditorialAccidentals(HTp sstart, HTp send);
		void     convertNextNoteToJAccidental(HTp current);
		void     fixTieStartEnd(HumdrumFile& infile);
		void     fixTiesStartEnd(HTp starts, HTp ends);

	private:
		std::vector<std::vector<int>> m_pstates;
		std::vector<std::vector<int>> m_kstates;
		std::vector<std::vector<bool>> m_estates;

};


class Tool_got2hum : public HumTool {
	public:
		         Tool_got2hum      (void);
		        ~Tool_got2hum      () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void    processFile        (const std::string& instring);
		void    initialize         (void);

	private:
		GotScore m_gotscore;

		bool m_editorialQ;
		bool m_cautionaryQ;
		bool m_gotQ;
		bool m_modern_accQ;
};


class Tool_grep : public HumTool {
	public:
		         Tool_grep         (void);
		        ~Tool_grep         () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void      processFile         (HumdrumFile& infile);
		void      initialize          (void);

	private:
		bool        m_negateQ;    // for the -v option
		std::string m_regex;      // for the -e option

};


class Tool_half : public HumTool {
	public:
		         Tool_half     (void);
		        ~Tool_half     () {};

		bool     run           (HumdrumFileSet& infiles);
		bool     run           (HumdrumFile& infile);
		bool     run           (const std::string& indata, std::ostream& out);
		bool     run           (HumdrumFile& infile, std::ostream& out);

	protected:
		void     initialize    (HumdrumFile& infile);
		void     processFile   (HumdrumFile& infile);
		void     halfRhythms   (HumdrumFile& infile);
		void     terminalLongToTerminalBreve(HumdrumFile& infile);
		void     adjustBeams   (HumdrumFile& infile);

	private:
		bool     m_lyricBreakQ = false;  // used with -l option

};


class Tool_hands : public HumTool {
	public:
		            Tool_hands        (void);
		           ~Tool_hands        () {};

		bool        run               (HumdrumFileSet& infiles);
		bool        run               (HumdrumFile& infile);
		bool        run               (const std::string& indata, std::ostream& out);
		bool        run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void        processFile       (HumdrumFile& infile);
		void        initialize        (void);
		void        colorHands        (HumdrumFile& infile);
		void        doHandAnalysis    (HumdrumFile& infile);
		void        doHandAnalysis    (HTp startSpine);
		void        markNotes         (HumdrumFile& infile);
		void        markNotes         (HTp sstart, HTp send);
		void        removeNotes       (HumdrumFile& infile, const std::string& htype);
		void        removeNotes       (HTp sstart, HTp send, const std::string& htype);

	private:
		bool        m_colorQ      = false;        // used with -c option
		std::string m_leftColor   = "dodgerblue"; // used with --left-color option
		std::string m_rightColor  = "crimson";    // used with --right-color option
		bool        m_markQ       = false;        // used with -m option
		std::string m_leftMarker  = "🟦";         //
		std::string m_rightMarker = "🟥";         //
		bool        m_leftOnlyQ   = false;        // used with -l option
		bool        m_rightOnlyQ  = false;        // used with -r option
		bool        m_attacksOnlyQ = false;       // used with -a option

		std::vector<int> m_trackHasHandMarkup;    // given track number uses hand labels

};


class HPNote {
	public:
		int track = -1;
		int line = -1;
		int field = -1;
		int subfield = -1;
		HTp token = NULL;
		HumNum duration = 0;
		std::string text;
		bool attack = false;
		bool nullQ = false;
};

class Tool_homorhythm : public HumTool {
	public:
		            Tool_homorhythm    (void);
		           ~Tool_homorhythm    () {};

		bool        run                (HumdrumFileSet& infiles);
		bool        run                (HumdrumFile& infile);
		bool        run                (const std::string& indata, std::ostream& out);
		bool        run                (HumdrumFile& infile, std::ostream& out);

	protected:
		void        processFile        (HumdrumFile& infile);
		void        analyzeLine        (HumdrumFile& infile, int line);
		void        initialize         (void);
		void        markHomophonicNotes(void);
		int         getExtantVoiceCount(HumdrumFile& infile);
		int         getOriginalVoiceCount(HumdrumFile& infile);
		void        addRawAnalysis     (HumdrumFile& infile, std::vector<double>& raw);
		void        addAccumulatedScores(HumdrumFile& infile, std::vector<double>& score);
		void        addAttacks         (HumdrumFile& infile, std::vector<int>& attacks);
		void        addFractionAnalysis(HumdrumFile& infile, std::vector<double>& score);

	private:
		std::vector<std::string> m_homorhythm;
		std::vector<int> m_notecount;
		std::vector<int> m_attacks;
		std::vector<std::vector<HPNote>> m_notes;
		double m_threshold = 4.0;
		double m_score = 1.0;
		double m_intermediate_score = 0.5;
		int m_voice_count = 0;
		bool m_letterQ = false;
};


class Tool_homorhythm2 : public HumTool {
	public:
		            Tool_homorhythm2    (void);
		           ~Tool_homorhythm2    () {};

		bool        run                (HumdrumFileSet& infiles);
		bool        run                (HumdrumFile& infile);
		bool        run                (const std::string& indata, std::ostream& out);
		bool        run                (HumdrumFile& infile, std::ostream& out);

	protected:
		void        processFile        (HumdrumFile& infile);
		void        initialize         (void);

	private:
		double      m_threshold = 0.6;
		double      m_threshold2 = 0.4;
		std::vector<double> m_score;
};


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



class Tool_humbreak : public HumTool {
	public:
		         Tool_humbreak     (void);
		        ~Tool_humbreak     () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void    processFile        (HumdrumFile& infile);
		void    initialize         (void);
		void    addBreaks          (HumdrumFile& infile);
		void    removeBreaks       (HumdrumFile& infile);
		void    convertPageToLine  (HumdrumFile& infile);
		void    markLineBreakMeasures(HumdrumFile& infile);

	private:
		std::map<int, int> m_lineMeasures;  // list of measures to add line breaks to
		std::map<int, int> m_pageMeasures;  // list of measures to add page breaks to

		std::map<int, int> m_lineOffset;  // measure offsets for measure breaks
		std::map<int, int> m_pageOffset;  // measure offsets for page breaks

		std::string m_group = "original";
		bool m_removeQ = false;
		bool m_page2lineQ = false;

};


// A TimePoint records the event times in a file.  These are positions of note attacks
// in the file.  The "index" variable keeps track of the line in the original file
// (for the first position in index), and other positions in index keep track of the
// equivalent line position of the timepoint in other file(s) that are being compared.
class TimePoint {
	public:
		// file: pointers to the file in which the index refers to
		std::vector<HumdrumFile*> file;

		// index :: A list of indexes for the lines at which the given timestamp
		// occurs in each file.  The first index is for the reference work.
		std::vector<int> index;

		// timestamp :: The duration from the start of the score to given time in score.
		HumNum timestamp = -1;

		// measure :: The measure number in which the timestamp occurs.
		int measure = -1;

		void clear(void) {
			file.clear();
			index.clear();
			timestamp = -1;
			measure = -1;
		}
};


// NotePoint is a note from a score that will be matches hopefully to an
// equivalent note in another score.
class NotePoint {
	public:
		HTp         token          = NULL;   // Humdrum token that contains note
		std::string subtoken;                // string that represents not (token may be chord)
		int         subindex       = -1;     // subtoken index of note (in chord)
		int         measure        = -1;     // measure number that note is found
		HumNum      measurequarter = -1;     // distance from start of measure to note
		int         track          = -1;     // track that note is from
		int         layer          = -1;     // layer that note is in
		HumNum      duration       = -1;     // duration (tied) of note
		int         b40            = -1;     // b40 pitch of note
		int         processed      = 0;      // has note been processed/matched
		int         sourceindex    = -1;     // source file index for note
		int         tpindex        = -1;     // timepoint index of note in source
		std::vector<int> matched;       // indexes to the location of the note in TimePoint list.
		                           // the index indicate which score the match is related to,
		                           // and a value of -1 means there is no equivalent timepoint.
		void clear(void) {
			token = NULL;
			subtoken = "";
			subindex = -1;
			measure = -1;
			measurequarter = -1;
			track = -1;
			layer = -1;
			duration = -1;
			b40 = -1;
			processed = 0;
			sourceindex = -1;
			tpindex = -1;
			matched.clear();
		}
};


// Function declarations:

class Tool_humdiff : public HumTool {
	public:
		         Tool_humdiff       (void);

		bool     run                (HumdrumFileSet& infiles);

	protected:
		void     compareFiles       (HumdrumFile& reference, HumdrumFile& alternate);

		void     compareTimePoints  (std::vector<std::vector<TimePoint>>& timepoints, HumdrumFile& reference, HumdrumFile& alternate);
		void     extractTimePoints  (std::vector<TimePoint>& points, HumdrumFile& infile);
		void     printTimePoints    (std::vector<TimePoint>& timepoints);
		void     compareLines       (HumNum minval, std::vector<int>& indexes, std::vector<std::vector<TimePoint>>& timepoints, std::vector<HumdrumFile*> infiles);
		void     getNoteList        (std::vector<NotePoint>& notelist, HumdrumFile& infile, int line, int measure, int sourceindex, int tpindex);
		int      findNoteInList     (NotePoint& np, std::vector<NotePoint>& nps);
		void     printNotePoints    (std::vector<NotePoint>& notelist);
		void     markNote           (NotePoint& np);

	private:
		int m_marked = 0;


};

std::ostream& operator<<(std::ostream& out, TimePoint& tp);
std::ostream& operator<<(std::ostream& out, NotePoint& np);



class Tool_humsheet : public HumTool {
	public:
		         Tool_humsheet       (void);
		        ~Tool_humsheet       () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

		void     printRowClasses   (HumdrumFile& infile, int row);
		void     printRowContents  (HumdrumFile& infile, int row);
		void     printRowData      (HumdrumFile& infile, int line);
      void     printCellClasses  (HTp token);
      void     printHtmlHeader   (void);
      void     printHtmlFooter   (void);
      void     printStyle        (HumdrumFile& infile);
      void     printJavascript   (void);
		void     printTitle        (HumdrumFile& infile, int line);

	protected:
		void     processFile       (HumdrumFile& infile);
		void     initialize        (void);
		void     analyzeTracks     (HumdrumFile& infile);
		void     printColSpan      (HTp token);
		void     printTabIndex     (HTp token);
		void     analyzeTabIndex   (HumdrumFile& infile);
		void     printId           (HTp token);
		void     printToken        (HTp token);
		void     printCellData     (HTp token);
		bool     isLayout          (HLp line);

	private:
		bool             m_exinterpQ       = false;
		bool             m_javascriptQ     = false;
		bool             m_idQ             = false;
		bool             m_htmlQ           = false;
		bool             m_zebraQ          = false;
		bool             m_zebra2Q         = false;
		bool             m_tabindexQ       = false;
		std::vector<int> m_max_subtrack;
		int              m_max_track       = 0;
		int              m_max_field       = 0;

};


class Tool_humsort : public HumTool {
	public:
		         Tool_humsort      (void);
		        ~Tool_humsort      () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void    processFile        (HumdrumFile& infile);

};


class Tool_humtr : public HumTool {
	public:
		            Tool_humtr        (void);
		           ~Tool_humtr        () {};

		bool        run               (HumdrumFileSet& infiles);
		bool        run               (HumdrumFile& infile);
		bool        run               (const std::string& indata, std::ostream& out);
		bool        run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void        processFile       (HumdrumFile& infile);
		void        initialize        (void);
		void        addFromToCombined (const std::string& value);
		void        fillFromToPair    (const std::string& from, const std::string& to);
		void        displayFromToTable(void);
		std::vector<std::string> getUtf8CharacterArray(const std::string& value);

		std::string transliterateText(const std::string& input);
		std::string transliterateTextNonOverlapping (const std::string& input);
		std::string transliterateTextOverlapping    (const std::string& input);
		void        processTextStrand      (HTp stok, HTp etok);
		void        convertTextSpines      (HumdrumFile& infile);
		void        convertLocalLayoutText (HumdrumFile& infile);
		void        convertGlobalLayoutText(HumdrumFile& infile);
		void        convertReferenceText   (HumdrumFile& infile);

	private:
		bool m_lyricsQ    = true;  // do not convert lyrics in **text spines.
		bool m_localQ     = true;  // do not convert t= fields in !LO: parameters.
		bool m_globalQ    = true;  // do not convert t= fields in !!LO: parameters.
		bool m_referenceQ = true;  // do not convert reference record values.

		bool m_lyricsOnlyQ;
		bool m_localOnlyQ;
		bool m_globalOnlyQ;
		bool m_referenceOnlyQ;

		std::string m_sep1  = " ";
		std::string m_sep2  = ":";

		std::vector<std::string> m_from;
		std::vector<std::string> m_to;

};


class Tool_imitation : public HumTool {
	public:
		         Tool_imitation    (void);
		        ~Tool_imitation    () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const string& indata, ostream& out);
		bool     run               (HumdrumFile& infile, ostream& out);

	protected:
		void    doAnalysis         (vector<vector<string>>& results, NoteGrid& grid,
		                            vector<vector<NoteCell*>>& attacks,
		                            vector<vector<double>>& intervals,
		                            HumdrumFile& infile, bool debug);
		void    analyzeImitation  (vector<vector<string>>& results,
		                            vector<vector<NoteCell*>>& attacks,
		                            vector<vector<double>>& intervals,
		                            int v1, int v2);
		void    getIntervals       (vector<double>& intervals,
		                            vector<NoteCell*>& attacks);
		int     compareSequences   (vector<NoteCell*>& attack1, vector<double>& seq1,
		                            int i1, vector<NoteCell*>& attack2,
		                            vector<double>& seq2, int i2);
		int     checkForIntervalSequence(vector<int>& m_intervals,
		                            vector<double>& v1i, int starti, int count);
		void    markedTiedNotes    (vector<HTp>& tokens);

	private:
	 	vector<HTp> m_kernspines;
		int m_threshold;
		bool m_duration;
		bool m_rest;
		bool m_rest2;
		double m_maxdistance;
		bool m_maxdistanceQ;
		vector<int> m_intervals;
		bool m_mark;
		char m_marker = '@';
		bool m_single = false;
		static int Enumerator;
		bool m_first = false;
		bool m_nozero = false;
		bool m_onlyzero = false;
		bool m_measure = false;
		bool m_beat    = false;
		bool m_length  = false;

		bool m_noInfo = false;

		bool m_noN    = false;
		bool m_noC    = false;
		bool m_noD    = false;
		bool m_noI    = false;

		bool m_noNN   = false;
		bool m_noCC   = false;
		bool m_noDD   = false;
		bool m_noII   = false;

		bool m_addsearches  = false;
		bool m_inversion  = false;
		bool m_retrograde = false;

		vector<int> m_barlines;
};


class Tool_instinfo : public HumTool {
	public:
		         Tool_instinfo      (void);
		        ~Tool_instinfo      () {};

		bool     run                (HumdrumFileSet& infiles);
		bool     run                (HumdrumFile& infile);
		bool     run                (const std::string& indata, std::ostream& out);
		bool     run                (HumdrumFile& infile, std::ostream& out);

	protected:
		void    processFile         (HumdrumFile& infile);
		void    initialize          (HumdrumFile& infile);
		void    updateInstrumentLine(HumdrumFile& infile, int inumIndex,
		                             std::map<int, std::string>& value,
		                             std::map<int, int>& track2kindex,
		                             const std::string& prefix);
		void    insertInstrumentInfo(HumdrumFile& infile, int index,
		                             std::map<int, std::string>& info, const std::string& prefix,
		                             const std::string& key, std::map<int, int>& track2kindex);
		void    printLine           (HumdrumFile& infile, int index);
		void    printLine           (HumdrumFile& infile, int index,
		                             const std::string& key);

	private:
		std::map<int, std::string> m_icode;  // instrument code, e.g., *Iflt
		std::map<int, std::string> m_iclass; // instrument class, e.g., *Iww
		std::map<int, std::string> m_iname;  // instrument name, e.g., *I"flute
		std::map<int, std::string> m_iabbr;  // instrument name, e.g., *I'flt.
		std::map<int, std::string> m_inum;   // instrument number, e.g., *I#2

};


class Tool_kern2mens : public HumTool {
	public:
		         Tool_kern2mens           (void);
		        ~Tool_kern2mens           () {};

		bool     run                      (HumdrumFileSet& infiles);
		bool     run                      (HumdrumFile& infile);
		bool     run                      (const string& indata, ostream& out);
		bool     run                      (HumdrumFile& infile, ostream& out);

	protected:
		void        convertToMens         (HumdrumFile& infile);
		std::string convertKernTokenToMens(HTp token);
		void        printBarline          (HumdrumFile& infile, int line);
		std::string getClefConversion     (HTp token);
		void        storeKernEditorialAccidental(HumdrumFile& infile);
		void        storeKernTerminalLong (HumdrumFile& infile);
		void        addVerovioStyling     (HumdrumFile& infile);
		void        analyzeColoration     (HumdrumFile& infile);
		void        analyzeColoration     (HTp infile);

	private:
		bool        m_numbersQ   = true; // used with -N option
		bool        m_measuresQ  = true; // used with -M option
		bool        m_invisibleQ = true; // used with -I option
		bool        m_doublebarQ = true; // used with -D option
		bool        m_noverovioQ = false; // used with -V option
		bool        m_evenNoteSpacingQ = false; // used with -e option
		std::string m_clef;              // used with -c option

		std::string m_kernEditorialAccidental;  // used with !!!RDF**kern:
		int         m_kernEdAccLineIndex = -1;
		std::string m_mensEdAccLine;

		std::string m_kernTerminalLong;  // used with !!!RDF**kern:
		int         m_kernTerminalLongIndex = -1;
		std::string m_mensTerminalLongLine;

};


class Tool_kernify : public HumTool {
	public:
		         Tool_kernify (void);
		        ~Tool_kernify () {};

		bool     run          (HumdrumFileSet& infiles);
		bool     run          (HumdrumFile& infile);
		bool     run          (const std::string& indata, std::ostream& out);
		bool     run          (HumdrumFile& infile, std::ostream& out);

	protected:
		void        initialize             (void);
		void        processFile            (HumdrumFile& infile);
		void        generateDummyKernSpine (HumdrumFile& infile);
		std::string makeNullLine           (HumdrumLine& line);
		std::string makeReverseLine        (HumdrumLine& line);
		bool        prepareDataSpines      (HumdrumFile& infile);
		bool        prepareDataSpine       (HTp spinestart);

	private:
		bool m_forceQ = false;  // used with -f option
		bool m_hasDataInterpretations = false;

};


class Tool_kernview : public HumTool {
	public:
		         Tool_kernview      (void);
		        ~Tool_kernview      () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void     processFile       (HumdrumFile& infile);
		void     initialize        (HumdrumFile& infile);
		std::string getKernString(HumdrumFile& infile, const std::string& list);

	private:
		std::string m_view_string;
		std::string m_hide_string;

};


class mei_staffDef {
	public:
		HumNum timestamp;
		string clef;           // such as *clefG2
		string timesig;        // such as *M4/4
		string keysig;         // such as *k[f#]
		string midibpm;        // such as *MM120
		string transpose;      // such as *Trd-1c-2
		int base40 = 0;        // used for transposing to C score
		string label;          // such as *I"violin 1
		string labelabbr;      // such as *I'v1
		bool mensural = false; // true if notationtype="mensural", "mensural.white" or "mensural.black"
		bool black = false;    // true if notationtype="mensural.black"
		int  maximodus = 0;    // number of longs in maxima (2 or 3)
		int  modus = 0;        // number of breves in long (2 or 3)
		int  tempus = 0;       // number of semibreves in breve (2 or 3)
		int  prolatio = 0;     // number of minims in semibreve (2 or 3)
		// always two semiminims in a minim
		// always two fusa in a semiminim
		// always two semifusa in a fusa

		void clear(void) {
			clef.clear();
			timesig.clear();
			keysig.clear();
			midibpm.clear();
			transpose.clear();
			base40 = 0;
			label.clear();
			labelabbr.clear();
		}
		mei_staffDef& operator=(mei_staffDef& staffDef) {
			if (this == &staffDef) {
				return *this;
			}
			clef       = staffDef.clef;
			timesig    = staffDef.timesig;
			keysig     = staffDef.keysig;
			midibpm    = staffDef.midibpm;
			transpose  = staffDef.transpose;
			base40     = staffDef.base40;
			label      = staffDef.label;
			labelabbr  = staffDef.labelabbr;
			mensural   = staffDef.mensural;
			black      = staffDef.black;
			maximodus  = staffDef.maximodus;
			modus      = staffDef.modus;
			tempus     = staffDef.tempus;
			prolatio   = staffDef.prolatio;
			return *this;
		}
		mei_staffDef(void) {
			// do nothing
		}
		mei_staffDef(const mei_staffDef& staffDef) {
			clef       = staffDef.clef;
			timesig    = staffDef.timesig;
			keysig     = staffDef.keysig;
			midibpm    = staffDef.midibpm;
			transpose  = staffDef.transpose;
			base40     = staffDef.base40;
			label      = staffDef.label;
			labelabbr  = staffDef.labelabbr;
			mensural   = staffDef.mensural;
			black      = staffDef.black;
			maximodus  = staffDef.maximodus;
			modus      = staffDef.modus;
			tempus     = staffDef.tempus;
			prolatio   = staffDef.prolatio;
		}
};


class mei_scoreDef {
	public:
		mei_staffDef global;
		vector<mei_staffDef> staves;
		void clear(void) {
			global.clear();
			staves.clear(); // or clear the contents of each staff...
		}
		void minresize(int count) {
			if (count < 1) {
				return;
			} else if (count < (int)staves.size()) {
				return;
			} else {
				staves.resize(count);
			}
		}
};


class hairpin_info {
	public:
		xml_node hairpin;
		GridMeasure *gm = NULL;
		int mindex = 0;
};


class grace_info {
	public:
		xml_node node; // note or chord
		string beamprefix;
		string beampostfix;
};


class Tool_mei2hum : public HumTool {
	public:
		        Tool_mei2hum    (void);
		       ~Tool_mei2hum    () {}

		bool    convertFile          (ostream& out, const char* filename);
		bool    convert              (ostream& out, xml_document& infile);
		bool    convert              (ostream& out, const char* input);
		bool    convert              (ostream& out, istream& input);

		void    setOptions           (int argc, char** argv);
		void    setOptions           (const vector<string>& argvlist);
		Options getOptionDefinitions (void);

	protected:
		void   initialize           (void);
		HumNum parseScore           (xml_node score, HumNum starttime);
		void   getChildrenVector    (vector<xml_node>& children, xml_node parent);
		void   parseScoreDef        (xml_node scoreDef, HumNum starttime);
		void   parseSectionScoreDef (xml_node scoreDef, HumNum starttime);
		void   processPgHead        (xml_node pgHead, HumNum starttime);
		void   processPgFoot        (xml_node pgFoot, HumNum starttime);
		void   processKeySig        (mei_staffDef& staffinfo, xml_node keysig, HumNum starttime);
		HumNum parseSection         (xml_node section, HumNum starttime);
		HumNum parseApp             (xml_node app, HumNum starttime);
		HumNum parseLem             (xml_node lem, HumNum starttime);
		HumNum parseRdg             (xml_node rdg, HumNum starttime);
		void   parseStaffGrp        (xml_node staffGrp, HumNum starttime);
		void   parseStaffDef        (xml_node staffDef, HumNum starttime);
		void   fillWithStaffDefAttributes(mei_staffDef& staffinfo, xml_node element);
		HumNum parseMeasure         (xml_node measure, HumNum starttime);
		HumNum parseStaff           (xml_node staff, HumNum starttime);
		HumNum parseStaff_mensural  (xml_node staff, HumNum starttime);
		void   parseReh             (xml_node reh, HumNum starttime);
		HumNum parseLayer           (xml_node layer, HumNum starttime, vector<bool>& layerPresent);
		HumNum parseLayer_mensural  (xml_node layer, HumNum starttime, vector<bool>& layerPresent);
		HumNum parseCorr_mensural   (xml_node corr, HumNum starttime);
		HumNum parseChoice_mensural (xml_node corr, HumNum starttime);
		HumNum parseLigature        (xml_node staff, HumNum starttime);
		int    extractStaffCountByFirstMeasure    (xml_node element);
		int    extractStaffCountByScoreDef        (xml_node element);
		HumNum parseRest            (xml_node chord, HumNum starttime);
		HumNum parseRest_mensural   (xml_node chord, HumNum starttime);
		HumNum parseMRest           (xml_node mrest, HumNum starttime);
		HumNum parseChord           (xml_node chord, HumNum starttime, int gracenumber);
		HumNum parseNote            (xml_node note, xml_node chord, string& output, HumNum starttime, int gracenumber);
		HumNum parseNote_mensural   (xml_node note, xml_node chord, string& output, HumNum starttime, int gracenumber);
		HumNum parseBeam            (xml_node note, HumNum starttime);
		HumNum parseTuplet          (xml_node note, HumNum starttime);
		void   parseClef            (xml_node clef, HumNum starttime);
		void   parseDynam           (xml_node dynam, HumNum starttime);
		void   parseHarm            (xml_node harm, HumNum starttime);
		void   parseTempo           (xml_node tempo, HumNum starttime);
		void   parseDir             (xml_node dir, HumNum starttime);
		HumNum getDuration          (xml_node element);
		HumNum getDuration_mensural (xml_node element, int& dotcount);
		string getHumdrumPitch      (xml_node note, vector<xml_node>& children);
		string getHumdrumRecip      (HumNum duration, int dotcount);
		void   buildIdLinkMap       (xml_document& doc);
		void   processNodeStartLinks(string& output, xml_node node,
		                             vector<xml_node>& nodelist);
		void   processNodeStopLinks(string& output, xml_node node,
		                             vector<xml_node>& nodelist);
		void   processPreliminaryLinkedNodes(xml_node node);
		void   processNodeStartLinks2(xml_node node, vector<xml_node>& nodelist);
		void   parseFermata         (string& output, xml_node node, xml_node fermata);
		void   parseSlurStart       (string& output, xml_node node, xml_node slur);
		void   parseSlurStop        (string& output, xml_node node, xml_node slur);
		void   parseTieStart        (string& output, xml_node node, xml_node tie);
		void   parseTieStop         (string& output, xml_node node, xml_node tie);
		void   parseArpeg           (string& output, xml_node node, xml_node arpeg);
		void   parseTrill           (string& output, xml_node node, xml_node trill);
		void   parseTupletSpanStart (xml_node node, xml_node tupletSpan);
		void   parseTupletSpanStop  (string& output, xml_node node, xml_node tupletSpan);
		void   parseSb              (xml_node sb, HumNum starttime);
		void   parsePb              (xml_node pb, HumNum starttime);
		void   processLinkedNodes   (string& output, xml_node node);
		int    getDotCount          (xml_node node);
		void   processFermataAttribute(string& output, xml_node node);
		string getNoteArticulations (xml_node note, xml_node chord);
		string getHumdrumArticulation(const string& tag, const string& humdrum,
		                              const string& attribute_artic,
		                              vector<xml_node>& element_artic,
		                              const string& chord_attribute_artic,
		                              vector<xml_node>& chord_element_artic);
		string setPlacement          (const string& placement);
		void   addFooterRecords      (HumdrumFile& outfile, xml_document& doc);
		void   addExtMetaRecords     (HumdrumFile& outfile, xml_document& doc);
		void   addHeaderRecords      (HumdrumFile& outfile, xml_document& doc);
		void   parseVerse            (xml_node verse, GridStaff* staff);
		string parseSyl              (xml_node syl);
		void   parseSylAttribute     (const string& attsyl, GridStaff* staff);
		void   reportVerseNumber     (int pmax, int staffindex);
		string getEditorialAccidental(vector<xml_node>& children);
		string getCautionaryAccidental(vector<xml_node>& children);
		string makeHumdrumClef       (const string& shape,
		                              const string& line,
		                              const string& clefdis,
		                              const string& clefdisplace);
		string cleanDirText          (const string& input);
		string cleanWhiteSpace       (const string& input);
		string cleanReferenceRecordText(const string& input);
		string cleanVerseText        (const string& input);
		bool   beamIsValid           (vector<xml_node>& beamlist);
		bool   beamIsGrace           (vector<xml_node>& beamlist);
		void   parseHairpin          (xml_node hairpin, HumNum starttime);
		void   processHairpins       (void);
		void   processHairpin        (hairpin_info& info);
		void   processGraceNotes     (HumNum timestamp);
		string prepareSystemDecoration(xml_node scoreDef);
		void   getRecursiveSDString  (string& output, xml_node current);
		void   parseBareSyl          (xml_node syl, GridStaff* staff);
		string getChildAccidGes      (vector<xml_node>& children);
		string getChildAccidVis      (vector<xml_node>& children);
		void   parseBarline          (xml_node barLine, HumNum starttime);

		// static functions
		static string accidToKern(const string& accid);

	private:
		Options        m_options;
		bool           m_stemsQ = false;
		bool           m_recipQ = false;
		bool           m_placeQ = false;
		bool           m_xmlidQ = false;

		mei_scoreDef   m_scoreDef;    // for keeping track of key/meter/clef etc.
		int            m_staffcount;  // number of staves in score.
		HumNum         m_tupletfactor = 1;
		HumGrid        m_outdata;
		int            m_currentLayer = 0;
		int            m_currentStaff = 0;
		int            m_maxStaffInFile = 0; // valid after parsing staves in first measure
		int            m_currentMeasure = -1;
		vector<int>    m_currentMeterUnit;
		string         m_beamPrefix;
		string         m_beamPostfix;
		bool           m_aboveQ = false;
		bool           m_belowQ = false;
		bool           m_editorialAccidentalQ = false;
		string         m_appLabel;
		string         m_systemDecoration;

		vector<int>    m_maxverse;
		vector<HumNum> m_measureDuration;
		vector<bool>   m_hasDynamics;
		vector<bool>   m_hasHarm;
		vector<bool>   m_hasXmlids;
		const int      m_maxstaff = 1000;

		bool           m_fermata = false;     // set priority of note/fermata over note@fermata
		vector<grace_info> m_gracenotes;      // buffer for storing grace notes
		HumNum			m_gracetime = 0;       // performance time of buffered grace notes
		bool           m_mensuralQ = false;

		HTp            lastNote = NULL;

		vector<hairpin_info> m_hairpins;

		map<string, vector<xml_node>> m_startlinks;
		map<string, vector<xml_node>> m_stoplinks;

};



class WordInfo {
	public:
		std::string word;                 // text of word
		int notes = 0;               // number of notes in word
		HumNum starttime;            // start time of word
		HumNum endtime;              // end time of word
		int bar = 0;                 // starting barline number for word
	  	std::vector<int> bars;            // starting barline number for each syllable
		std::vector<std::string> syllables;    // list of syllables in word with melisma
		std::vector<int> notecounts;      // list of note counts for each syllable in word
		std::vector<HumNum> starttimes;   // list of start times for each syllable
		std::vector<HumNum> endtimes;     // list of end times for each syllable
		HumNum duration(void) { return endtime - starttime; }
		std::string name;
		std::string abbreviation;
		int partnum = 0;
		void clear(void) {
			starttime = 0;
			endtime   = 0;
			partnum   = 0;
			notes     = 0;
			bar       = 0;
			abbreviation.clear();
			notecounts.clear();
			starttimes.clear();
			syllables.clear();
			endtimes.clear();
			word.clear();
			name.clear();
			bars.clear();
		}
};


class Tool_melisma : public HumTool {
	public:
		      Tool_melisma             (void);
		     ~Tool_melisma             () {};

		bool  run                      (HumdrumFileSet& infiles);
		bool  run                      (HumdrumFile& infile);
		bool  run                      (const std::string& indata, std::ostream& out);
		bool  run                      (HumdrumFile& infile, std::ostream& out);

	protected:
		void   initialize              (HumdrumFile& infile);
		void   processFile             (HumdrumFile& infile);
		void   getNoteCounts           (HumdrumFile& infile, std::vector<std::vector<int>>& counts);
		void   getNoteCountsForLyric   (std::vector<std::vector<int>>& counts, HTp lyricStart);
		int    getCountForSyllable     (HTp token);
		void   replaceLyrics           (HumdrumFile& infile, std::vector<std::vector<int>>& counts);
		void   markMelismas            (HumdrumFile& infile, std::vector<std::vector<int>>& counts);
		void   markMelismaNotes        (HTp text, int count);
		void   extractWordlist         (std::vector<WordInfo>& wordinfo, std::map<std::string, int>& wordlist,
		                                HumdrumFile& infile, std::vector<std::vector<int>>& notecount);
		std::string extractWord             (WordInfo& winfo, HTp token, std::vector<std::vector<int>>& counts);
		HumNum getEndtime              (HTp text);
		void   printWordlist           (HumdrumFile& infile, std::vector<WordInfo>& wordinfo,
		                                std::map<std::string, int>);
		void   initializePartInfo      (HumdrumFile& infile);
		void   getMelismaNoteCounts    (std::vector<int>& ncounts, std::vector<int>& mcounts,
		                                HumdrumFile& infile);
		double getScoreDuration        (HumdrumFile& infile);
		void   initBarlines            (HumdrumFile& infile);

	private:
		std::vector<std::vector<HumNum>> m_endtimes;      // end time of syllables indexed by line/field
		std::vector<std::string>         m_names;         // name of parts indexed by track
		std::vector<std::string>         m_abbreviations; // abbreviation of parts indexed by track
		std::vector<int>            m_partnums;      // part number index by track
		std::vector<int>            m_measures;      // current measure number

};



class Tool_mens2kern : public HumTool {
	public:
		         Tool_mens2kern      (void);
		        ~Tool_mens2kern      () {};

		bool     run                 (HumdrumFileSet& infiles);
		bool     run                 (HumdrumFile& infile);
		bool     run                 (const std::string& indata, std::ostream& out);
		bool     run                 (HumdrumFile& infile, std::ostream& out);

	protected:
		void     processFile         (HumdrumFile& infile);
		void     initialize          (void);
		void     processMelody       (std::vector<HTp>& melody);
		std::string mens2kernRhythm  (const std::string& rhythm,
		                              bool altera,  bool perfecta,
		                              bool imperfecta, int maxima_def, int longa_def,
		                              int brevis_def, int semibrevis_def);
		void     getMensuralInfo     (HTp token, int& maximodus, int& modus,
		                              int& tempus, int& prolatio);
		std::string getClefConversion(HTp token);

	private:
		bool     m_debugQ;


};


class Tool_meter : public HumTool {

	public:
		         Tool_meter        (void);
		        ~Tool_meter        () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);


	protected:
		void     initialize        (void);
		void     processFile       (HumdrumFile& infile);
		void     getMeterData      (HumdrumFile& infile);
		void     processLine       (HumdrumLine& line,
		                            std::vector<HumNum>& curNum,
		                            std::vector<HumNum>& curDen,
		                            std::vector<HumNum>& curBeat,
		                            std::vector<HumNum>& curBarTime);
		void     printMeterData    (HumdrumFile& infile);
		void     printHumdrumLine  (HumdrumLine& line, bool printLabels);
		int      printKernAndAnalysisSpine(HumdrumLine& line, int index, bool printLabels, bool forceInterpretation = false);
		HumNum   getHumNum          (HTp token, const std::string& parameter);
		std::string getHumNumString(HumNum input);
		bool     searchForLabels   (HumdrumLine& line);
		void     printLabelLine    (HumdrumLine& line);
		void     analyzePickupMeasures(HumdrumFile& infile);
		void     analyzePickupMeasures(HTp sstart);
		HumNum   getTimeSigDuration(HTp tsig);
		void     markPickupContent (HTp stok, HTp etok);

	private:

		bool     m_commaQ       = false;
		bool     m_debugQ       = false;
		bool     m_denominatorQ = false;
		bool     m_eighthQ      = false;
		bool     m_floatQ       = false;
		bool     m_halfQ        = false;
		bool     m_joinQ        = false;
		bool     m_nobeatQ      = false;
		bool     m_nolabelQ     = false;
		bool     m_numeratorQ   = false;
		bool     m_quarterQ     = false;
		bool     m_restQ        = false;
		bool     m_sixteenthQ   = false;
		bool     m_tsigQ        = false;
		bool     m_wholeQ       = false;
		bool     m_zeroQ        = false;
		int      m_digits       = 0;

};


class Tool_metlev : public HumTool {
	public:
		      Tool_metlev      (void);
		     ~Tool_metlev      () {};

		bool  run              (HumdrumFileSet& infiles);
		bool  run              (HumdrumFile& infile);
		bool  run              (const std::string& indata, std::ostream& out);
		bool  run              (HumdrumFile& infile, std::ostream& out);

	protected:
		void  fillVoiceResults (std::vector<std::vector<double> >& results,
		                        HumdrumFile& infile,
		                        std::vector<double>& beatlev);

	private:
		std::vector<HTp> m_kernspines;

};



class Tool_modori : public HumTool {
	public:
		         Tool_modori                  (void);
		        ~Tool_modori                  () {};

		bool     run                          (HumdrumFileSet& infiles);
		bool     run                          (HumdrumFile& infile);
		bool     run                          (const std::string& indata, std::ostream& out);
		bool     run                          (HumdrumFile& infile, std::ostream& out);

	protected:
		void     processFile                  (HumdrumFile& infile);
		void     initialize                   (void);
		void     printInfo                    (void);
		void     switchModernOriginal         (HumdrumFile& infile);
		bool     swapKeyStyle                 (HTp one, HTp two);
		bool     swapClefStyle                (HTp one, HTp two);
		bool     swapInstrumentAbbreviationStyle(HTp one, HTp two);
		bool     swapInstrumentNameStyle      (HTp one, HTp two);
		bool     flipMensurationStyle         (HTp token);

		void     convertKeySignatureToModern  (HTp token);
		void     convertKeySignatureToOriginal(HTp token);
		void     convertKeySignatureToRegular (HTp token);

		void     convertClefToModern          (HTp token);
		void     convertClefToOriginal        (HTp token);
		void     convertClefToRegular         (HTp token);

		void     convertMensurationToModern   (HTp token);
		void     convertMensurationToOriginal (HTp token);
		void     convertMensurationToRegular  (HTp token);

		void     convertInstrumentNameToModern   (HTp token);
		void     convertInstrumentNameToOriginal (HTp token);
		void     convertInstrumentNameToRegular  (HTp token);

		void     convertInstrumentAbbreviationToModern   (HTp token);
		void     convertInstrumentAbbreviationToOriginal (HTp token);
		void     convertInstrumentAbbreviationToRegular  (HTp token);

		int      getPairedReference           (int index, std::vector<std::string>& keys);
		void     storeModOriReferenceRecords  (HumdrumFile& infile);
		void     processExclusiveInterpretationLine(HumdrumFile& infile, int line);
		bool     processStaffCompanionSpines  (std::vector<HTp> tokens);
		bool     processStaffSpines           (std::vector<HTp>& tokens);
		void     updateLoMo                   (HumdrumFile& infile);
		void     processLoMo                  (HTp lomo);
		void     printModoriOutput            (HumdrumFile& infile);
		bool     swapMensurationStyle         (HTp one, HTp two);

	private:
		bool m_modernQ        = false; // -m option: show modern key/clef/time signatures
		bool m_originalQ      = false; // -o option: show original key/clef/mensuration
		bool m_infoQ          = false; // show key/clef/mensuration tokens in data

		bool m_nokeyQ         = false; // -K option: don't change key signatures
		bool m_noclefQ        = false; // -C option: don't change clefs
		bool m_nomensurationQ = false; // -M option: don't change mensurations
		bool m_nolyricsQ      = false; // -L option: don't change **text
		bool m_nolotextQ      = false; // -T option: don't change !LO:TX
		bool m_norefsQ        = false; // -R option: don't change !LO:TX
		bool m_nolabelsQ      = false; // -L option: don't change *I"
		bool m_nolabelAbbrsQ  = false; // -A option: don't change *I"

		std::vector<std::map<HumNum, std::vector<HTp>>> m_keys;
		std::vector<std::map<HumNum, std::vector<HTp>>> m_clefs;
		std::vector<std::map<HumNum, std::vector<HTp>>> m_mensurations;
		std::vector<std::map<HumNum, std::vector<HTp>>> m_labels;
		std::vector<std::map<HumNum, std::vector<HTp>>> m_labelAbbrs;
		std::vector<std::pair<HTp, HTp>> m_references;
		std::vector<HTp> m_lyrics;
		std::vector<HTp> m_lotext;
		std::vector<HTp> m_lomo;

};



class SonorityNoteData {
	public:

		SonorityNoteData(void) {
			clear();
		}

		void clear(void) {
			m_token = NULL;
			m_tok.clear();
			m_accidentalQ = false;
			m_upperQ = false;
			m_attackQ = false;
			m_index = 0;
			m_base7 = -1;
			m_base12 = -1;
			m_base40 = -1;
		}

		ostream& print(ostream& out) {
			out << "NOTE:\t"   << m_token   << endl;
			out << "\tINDEX:\t"  << m_index   << endl;
			out << "\tSTRING:\t" << m_tok     << endl;
			out << "\tATTACK:\t" << m_attackQ << endl;
			out << "\tBASE7:\t"  << m_base7   << endl;
			out << "\tBASE40:\t" << m_base40  << endl;
			return out;
		}

		void setToken(HTp token, bool nullQ, int index) {
			m_attackQ = true;
			if (nullQ) {
				m_attackQ = false;
			}
			m_token = token;
			m_index = index;
			if (token->isChord()) {
				m_tok = token->getSubtoken(index);
			} else {
				m_tok = *token;
				m_index = 0;
			}
			if (m_tok.find('_') != std::string::npos) {
				m_attackQ = false;
			}
			if (m_tok.find(']') != std::string::npos) {
				m_attackQ = false;
			}
			m_base7 = Convert::kernToBase7(m_tok);
			m_base12 = Convert::kernToBase12(m_tok);
			m_base40 = Convert::kernToBase40(m_tok);
		}

		void setString(std::string tok) {
			// tok cannot be a chord or a null token
			// This version is for vertical queries not for searching data.
			m_attackQ = true;
			m_token = NULL;
			m_index = 0;
			m_tok = tok;
			if (m_tok.find('_') != std::string::npos) {
				m_attackQ = false;
			}
			if (m_tok.find(']') != std::string::npos) {
				m_attackQ = false;
			}
			m_base7 = Convert::kernToBase7(m_tok);
			m_base12 = Convert::kernToBase12(m_tok);
			m_base40 = Convert::kernToBase40(m_tok);

			if (m_tok.find('n') != std::string::npos) {
				m_accidentalQ = true;
			} if (m_tok.find('-') != std::string::npos) {
				m_accidentalQ = true;
			} if (m_tok.find('#') != std::string::npos) {
				m_accidentalQ = true;
			}
			for (int i=0; i<(int)m_tok.size(); i++) {
				if (isupper(m_tok[i])) {
					m_upperQ = true;
				}
				break;
			}
		}

		bool hasAccidental(void) {
			// Set only with setText() input.
			return m_accidentalQ;
		}

		bool hasUpperCase(void) {
			// Set only with setText() input.
			return m_upperQ;
		}

		bool isValid(void)     { return m_token != NULL;    }
		HTp  getToken(void)    { return m_token;            }
		std::string getText(void) { return m_tok;           }
		int  getIndex(void)    { return m_index;            }
		bool isAttack(void)    { return m_attackQ;          }
		bool isSustain(void)   { return !m_attackQ;         }
		int  getBase12(void)   { return (int)m_base12;      }
		int  getBase12Pc(void) { return (int)m_base12 % 7;  }
		int  getBase7(void)    { return (int)m_base7;       }
		int  getBase7Pc(void)  { return (int)m_base7 % 7;   }
		int  getBase40(void)   { return (int)m_base40;      }
		int  getBase40Pc(void) { return (int)m_base40 % 40; }

	private:
		HTp m_token;
		std::string m_tok;  // note string from token
		bool m_accidentalQ; // note contains an accidental
		bool m_upperQ;      // Diatonic note name contains an upper case letter
		bool m_attackQ;     // true if note is an attack
		char m_index;       // chord index of note (zero offset)
		char m_base7;       // pitch in base-7 representation
		char m_base12;      // pitch in base-12 representation
		short int m_base40; // pitch in base-40 representation
};



class SonorityDatabase {
	public:
		SonorityDatabase(void) { clear(); }
		void clear(void)       { m_notes.clear(); m_line = NULL; }
		int getCount(void)     { return (int)m_notes.size(); }
		int getNoteCount(void) { return (int)m_notes.size(); }
		int getSize(void)      { return (int)m_notes.size(); }
		bool isEmpty(void)     { return m_notes.empty(); }
		HLp getLine(void)      { return m_line; }
		SonorityNoteData& getLowest(void) { return m_lowest; };
		void addNote          (const std::string& text);
		void buildDatabase     (HLp line);
		SonorityNoteData& operator[](int index) {
			return m_notes.at(index);
		}
	protected:
		void expandList(void) {
			m_notes.resize(m_notes.size() + 1);
		}

	private:
		SonorityNoteData m_lowest;
		std::vector<SonorityNoteData> m_notes;
		HLp m_line = NULL;
};


//////////////////////////////
//
// MSearchQueryToken -- one element of the music search.  This is a combined
//    search of pitch, interval, rhythm and harmony.
//

class MSearchQueryToken {
	public:
		MSearchQueryToken(void) {
			clear();
		}
		MSearchQueryToken(const MSearchQueryToken& token) {
			anything    = token.anything;
			anypitch    = token.anypitch;
			anyinterval = token.anyinterval;
			anyrhythm   = token.anyrhythm;
			pc          = token.pc;
			base        = token.base;
			direction   = token.direction;
			dinterval   = token.dinterval;
			cinterval   = token.cinterval;
			duration    = token.duration;
			rhythm      = token.rhythm;
			harmonic    = token.harmonic;
			hpieces     = token.hpieces;
			hquery      = token.hquery;
		}
		MSearchQueryToken& operator=(const MSearchQueryToken& token) {
			if (this == &token) {
				return *this;
			}
			anything    = token.anything;
			anypitch    = token.anypitch;
			anyinterval = token.anyinterval;
			anyrhythm   = token.anyrhythm;
			pc          = token.pc;
			base        = token.base;
			direction   = token.direction;
			dinterval   = token.dinterval;
			harmonic    = token.harmonic;
			hpieces     = token.hpieces;
			hquery      = token.hquery;
			cinterval   = token.cinterval;
			duration    = token.duration;
			rhythm      = token.rhythm;
			return *this;
		}
		void clear(void) {
			anything     = true;
			anypitch     = true;
			anyrhythm    = true;
			anyinterval  = true;
			pc           = NAN;
			base         = 0;
			direction    = -123456789; // interval direction
			dinterval    = -123456789; // diatonic interval
			cinterval    = -123456789; // chromatic interval
			duration     = -1;
			harmonic     = "";
			hpieces.clear();
			hquery.clear();
			rhythm       = "";
		}
		void parseHarmonicQuery(void);

		bool   anything    = true;  // element can match any note/rest
		bool   anypitch    = true;  // element can match any pitch class
		bool   anyrhythm   = true;  // element can match any rhythm
		bool   anyinterval = true;  // element can match any interval

		// pitch features
		double pc;           // NAN = rest
		int    base;

		// interval features:
		int    direction;   // which melodic direction for interval?
		int    dinterval;   // diatonic interval
		int    cinterval;   // chromatic interval (base-40; up to 2 sharps/flats)
		std::string harmonic; // harmonic query
		std::vector<std::string> hpieces;
		std::vector<SonorityNoteData> hquery;

		// rhythm features:
		HumNum duration;
		std::string rhythm;
};


ostream& operator<<(ostream& out, MSearchQueryToken& item);

class MSearchTextQuery {
	public:
		MSearchTextQuery(void) {
			clear();
		}
		MSearchTextQuery(const MSearchTextQuery& token) {
			word = token.word;
			link = token.link;
		}
		MSearchTextQuery& operator=(const MSearchTextQuery& token) {
			if (this == &token) {
				return *this;
			}
			word = token.word;
			link = token.link;
			return *this;
		}
		void clear(void) {
			word.clear();
			link = false;
		}
		std::string word;
		bool link = false;
};


class TextInfo {
	public:
		TextInfo(void) {
			clear();
		}
		TextInfo(const TextInfo& info) {
			fullword = info.fullword;
			starttoken = info.starttoken;
			nexttoken = info.nexttoken;
		}
		TextInfo& operator=(const TextInfo& info) {
			if (this == &info) {
				return *this;
			}
			fullword = info.fullword;
			starttoken = info.starttoken;
			nexttoken = info.nexttoken;
			return *this;
		}
		void clear(void) {
			fullword.clear();
			starttoken = NULL;
			nexttoken = NULL;
		}
		std::string fullword;
		HTp starttoken;
		HTp nexttoken;
};


class Tool_msearch : public HumTool {
	public:
		         Tool_msearch      (void);
		        ~Tool_msearch      () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, ostream& out);
		bool     run               (HumdrumFile& infile, ostream& out);

	protected:
		void    initialize         (void);
		void    doMusicSearch      (HumdrumFile& infile, NoteGrid& grid,
		                            vector<MSearchQueryToken>& query);
		bool    doHarmonicPitchSearch(MSearchQueryToken& query, HTp token);
		void    doTextSearch       (HumdrumFile& infile, NoteGrid& grid,
		                            vector<MSearchTextQuery>& query);
		void    fillMusicQuery     (vector<MSearchQueryToken>& query);
		void    fillMusicQueryInterleaved(vector<MSearchQueryToken>& query,
		                            const std::string& input, bool rhythmQ = false);
		void    fillMusicQueryPitch(vector<MSearchQueryToken>& query,
		                            const std::string& input);
		void    fillMusicQueryInterval(vector<MSearchQueryToken>& query,
		                            const std::string& input);
		void    fillMusicQueryRhythm(vector<MSearchQueryToken>& query,
		                            const std::string& input);
		void    fillTextQuery      (vector<MSearchTextQuery>& query,
		                            const std::string& input);
		bool    checkForMusicMatch(vector<NoteCell*>& notes, int index,
		                            vector<MSearchQueryToken>& dpcQuery,
		                            vector<NoteCell*>& match);
		void    markMatch          (HumdrumFile& infile,
		                            vector<NoteCell*>& match);
		void    storeMatch         (vector<NoteCell*>& match);
		void    markTextMatch      (HumdrumFile& infile, TextInfo& word);
		void    fillWords          (HumdrumFile& infile,
		                            vector<TextInfo*>& words);
		void    fillWordsForTrack  (vector<TextInfo*>& words,
		                            HTp starttoken);
		void    printQuery         (vector<MSearchQueryToken>& query);
		void    addMusicSearchSummary(HumdrumFile& infile, int mcount, const std::string& marker);
		void    addTextSearchSummary(HumdrumFile& infile, int mcount, const std::string& marker);
		void    addMatch           (HumdrumFile& infile, vector<NoteCell*>& match);
		int     makeBase40Interval (int diatonic, const std::string& alteration);
		std::string convertPitchesToIntervals(const std::string& input);
		void    markNote           (HTp token, int index);
		int     checkHarmonicPitchMatch (SonorityNoteData& query,
		                           SonorityDatabase& sonorities, bool suppressQ);
		bool    checkVerticalOnly  (const std::string& input);
		void    makeLowerCase      (std::string& inout);

	private:
	 	vector<HTp> m_kernspines;
		std::string m_text;
		std::string m_marker;
		bool        m_verticalOnlyQ = false;
		bool        m_markQ      = false;
		bool        m_quietQ     = false;
		bool        m_debugQ     = false;
		bool        m_nooverlapQ = false;
		std::vector<int> m_barnums;
		std::vector<std::vector<NoteCell*>> m_matches;
		std::vector<SonorityDatabase> m_sonorities;
		std::vector<bool> m_sonoritiesChecked;
		std::vector<pair<HTp, int>> m_tomark;
};


class Tool_musedata2hum : public HumTool {
	public:
		        Tool_musedata2hum    (void);
		       ~Tool_musedata2hum    () {}

		bool    convertFile          (ostream& out, const string& filename);
		bool    convertString        (ostream& out, const string& input);
		bool    convert              (ostream& out, MuseDataSet& mds);
		bool    convert              (ostream& out, istream& input);

		void    setOptions           (int argc, char** argv);
		void    setOptions           (const std::vector<std::string>& argvlist);
		Options getOptionDefinitions (void);
		void    setInitialOmd        (const string& omd);

	protected:
		void    initialize           (void);
		void    convertLine          (GridMeasure* gm, MuseRecord& mr);
		bool    convertPart          (HumGrid& outdata, MuseDataSet& mds, int index, int partindex, int partcount);
		int     convertMeasure       (HumGrid& outdata, MuseData& part, int partindex, int startindex);
		GridMeasure* getMeasure      (HumGrid& outdata, HumNum starttime);
		void    setTimeSigDurInfo    (const std::string& mtimesig);
		void    setMeasureStyle      (GridMeasure* gm, MuseRecord& mr);
		void    setMeasureNumber     (GridMeasure* gm, MuseRecord& mr);
		void    storePartName        (HumGrid& outdata, MuseData& part, int index);
		void    addNoteDynamics      (GridSlice* slice, int part,
		                              MuseRecord& mr);
		void    addLyrics            (GridSlice* slice, int part, int staff, MuseRecord& mr);
		void    addFiguredHarmony    (MuseRecord& mr, GridMeasure* gm,
		                              HumNum timestamp, int part, int maxstaff);
		std::string cleanString      (const std::string& input);
		void    addTextDirection     (GridMeasure* gm, int part, int staff,
		                              MuseRecord& mr, HumNum timestamp);
		void    addAboveBelowKernRdf (void);
		bool    needsAboveBelowKernRdf(void);
		void    addDirectionDynamics(GridSlice* slice, int part, MuseRecord& mr);
		void    printLine           (std::ostream& out, HumdrumLine& line);

	private:
		// options:
		Options m_options;
		bool m_stemsQ = false;         // used with -s option
		bool m_recipQ = false;         // used with -r option
      std::string m_group = "score"; // used with -g option
		std::string m_omd = "";        // initial tempo designation (store for later output)
		bool m_noOmvQ = false;         // used with --omd option

		// state variables:
		int m_part     = 0;            // staff index currently being processed
		int m_maxstaff = 0;            // total number of staves (parts)
		HumNum m_timesigdur = 4;       // duration of current time signature in quarter notes
		HTp m_lastfigure = NULL;       // last figured bass token
		int m_lastbarnum = -1;         // barnumber carried over from previous bar
		HTp m_lastnote = NULL;         // for dealing with chords.
		double m_tempo = 0.0;          // for initial tempo from MIDI settings
		bool m_aboveBelowKernRdf = false; // output RDF**kern above/below markers

		// m_measureLineIndex -- keep track of index for processed
		// measure for debugging.
		int m_measureLineIndex = -1;

		// m_figuredOffset -- increment for the next figure bass offset.
		int m_figureOffset = 0;

		// m_quarterDivisions -- currently processed $Q value.
		int m_quarterDivisions = 0;

		std::map<std::string, bool> m_usedReferences;
		std::vector<std::string> m_postReferences;

};



class MusicXmlHarmonyInfo {
	public:
		HTp    token;
		HumNum timestamp;
		int    partindex;
};

class MusicXmlFiguredBassInfo {
	public:
		HTp    token;
		HumNum timestamp;
		int    partindex;
};


class Tool_musicxml2hum : public HumTool {
	public:
		        Tool_musicxml2hum    (void);
		       ~Tool_musicxml2hum    () {}

		bool    convertFile          (ostream& out, const char* filename);
		bool    convert              (ostream& out, pugi::xml_document& infile);
		bool    convert              (ostream& out, const char* input);
		bool    convert              (ostream& out, istream& input);

		void    setOptions           (int argc, char** argv);
		void    setOptions           (const std::vector<std::string>& argvlist);
		Options getOptionDefinitions (void);

	protected:
		void   initialize           (void);
		std::string getChildElementText  (pugi::xml_node root, const char* xpath);
		std::string getChildElementText  (pugi::xpath_node root, const char* xpath);
		std::string getAttributeValue    (pugi::xml_node xnode, const std::string& target);
		std::string getAttributeValue    (xpath_node xnode, const std::string& target);
		void   printAttributes      (pugi::xml_node node);
		bool   getPartInfo          (map<std::string, pugi::xml_node>& partinfo,
		                             std::vector<std::string>& partids, pugi::xml_document& doc);
		bool   stitchParts          (HumGrid& outdata,
		                             std::vector<std::string>& partids,
		                             map<std::string, pugi::xml_node>& partinfo,
		                             map<std::string, pugi::xml_node>& partcontent,
		                             std::vector<MxmlPart>& partdata);
		bool   getPartContent       (map<std::string, pugi::xml_node>& partcontent,
		                             std::vector<std::string>& partids, pugi::xml_document& doc);
		void   printPartInfo        (std::vector<std::string>& partids,
		                             map<std::string, pugi::xml_node>& partinfo,
		                             map<std::string, pugi::xml_node>& partcontent,
		                             std::vector<MxmlPart>& partdata);
		bool   fillPartData         (std::vector<MxmlPart>& partdata,
		                             const std::vector<std::string>& partids,
		                             map<std::string, pugi::xml_node>& partinfo,
		                             map<std::string, pugi::xml_node>& partcontent);
		bool   fillPartData         (MxmlPart& partdata, const std::string& id,
		                             pugi::xml_node partdeclaration,
		                             pugi::xml_node partcontent);
		void   appendZeroEvents     (GridMeasure* outfile,
		                             std::vector<SimultaneousEvents*>& nowevents,
		                             HumNum nowtime,
		                             std::vector<MxmlPart>& partdata);
		void   handleFiguredBassWithoutNonZeroEvent (std::vector<SimultaneousEvents*>& nowevents, HumNum nowtime);
		void   appendNonZeroEvents   (GridMeasure* outdata,
		                              std::vector<SimultaneousEvents*>& nowevents,
		                              HumNum nowtime,
		                              std::vector<MxmlPart>& partdata);
		void   addGraceLines         (GridMeasure* outdata,
		                              std::vector<std::vector<std::vector<std::vector<MxmlEvent*>>>>& notes,
		                              std::vector<MxmlPart>& partdata, HumNum nowtime);
		void   addEventToList        (std::vector<std::vector<std::vector<std::vector<MxmlEvent*>>>>& list,
		                              MxmlEvent* event);
		void   addHeaderRecords      (HumdrumFile& outfile, pugi::xml_document& doc);
		void   addFooterRecords      (HumdrumFile& outfile, pugi::xml_document& doc);
		std::string& cleanSpaces     (std::string& input);
		std::string cleanSpacesAndColons(const std::string& input);
		void setEditorialAccidental  (int accidental, GridSlice* slice,
		                              int partindex, int staffindex, int voiceindex);
		void moveBreaksToEndOfPreviousMeasure(HumGrid& outdata);

		bool convert          (ostream& out);
		bool convertPart      (ostream& out, const std::string& partname,
		                       int partindex);
		bool insertMeasure    (HumGrid& outdata, int mnum,
		                       std::vector<MxmlPart>& partdata,
		                       std::vector<int> partstaves);
		bool convertNowEvents (GridMeasure* outdata,
		                       std::vector<SimultaneousEvents*>& nowevents,
		                       std::vector<int>& nowparts,
		                       HumNum nowtime,
		                       std::vector<MxmlPart>& partdata,
		                       std::vector<int>& partstaves);
		void appendNullTokens (HLp line, MxmlPart& part);
		void appendEvent      (HLp line, MxmlEvent* event);
		void insertExclusiveInterpretationLine(HumdrumFile& outfile,
		                       std::vector<MxmlPart>& partdata);
		void insertAllToken   (HumdrumFile& outfile, std::vector<MxmlPart>& partdata,
		                       const std::string& common);
		void insertSingleMeasure(HumdrumFile& outfile);
		void cleanupMeasures   (HumdrumFile& outfile,
		                        std::vector<HLp> measures);
		void processPrintElement(GridMeasure* outdata, pugi::xml_node element, HumNum timestamp);
		void insertOffsetHarmonyIntoMeasure(GridMeasure* gm);
		void insertOffsetFiguredBassIntoMeasure(GridMeasure* gm);

		void addStriaLine      (GridMeasure* outdata,
		                        std::vector<std::vector<xml_node> >& stafflines,
		                        std::vector<MxmlPart>& partdata,
                              HumNum nowtime);
		void addClefLine       (GridMeasure* outdata, std::vector<std::vector<pugi::xml_node>>& clefs,
		                        std::vector<MxmlPart>& partdata, HumNum nowtime);
		void addOttavaLine     (GridMeasure* outdata, std::vector<std::vector<std::vector<pugi::xml_node>>>& ottavas,
		                        std::vector<MxmlPart>& partdata, HumNum nowtime);
		void storeOttava       (int pindex, xml_node octaveShift, xml_node direction,
		                        std::vector<std::vector<std::vector<xml_node>>>& ottavas);
		void insertPartClefs   (pugi::xml_node clef, GridPart& part);
		void insertPartStria   (int lines, GridPart& part);
		void insertPartOttavas (pugi::xml_node ottava, GridPart& part, int partindex, int partstaffindex, int staffcount);
		pugi::xml_node convertClefToHumdrum(pugi::xml_node clef, HTp& token, int& staffindex);
		pugi::xml_node convertOttavaToHumdrum(pugi::xml_node ottava, HTp& token, int& staffindex,
		                        int partindex, int partstaffindex, int staffcount);

		void addTranspositionLine(GridMeasure* outdata, std::vector<std::vector<pugi::xml_node>>& transpositions,
		                       std::vector<MxmlPart>& partdata, HumNum nowtime);
		void addKeySigLine    (GridMeasure* outdata, std::vector<std::vector<pugi::xml_node>>& keysigs,
		                        std::vector<MxmlPart>& partdata, HumNum nowtime);
		void addKeyDesignationLine(GridMeasure* outdata, vector<vector<xml_node>>& keydesigs,
		                        vector<MxmlPart>& partdata, HumNum nowtime);
		void insertPartKeySigs (pugi::xml_node keysig, GridPart& part);
		void insertPartKeyDesignations(xml_node keydeg, GridPart& part);
		pugi::xml_node convertKeySigToHumdrum(pugi::xml_node keysig,
		                        HTp& token, int& staffindex);
		pugi::xml_node convertKeySigToHumdrumKeyDesignation(xml_node keysig,
		                        HTp& token, int& staffindex);

		void addTimeSigLine    (GridMeasure* outdata, std::vector<std::vector<pugi::xml_node>>& timesigs,
		                        std::vector<MxmlPart>& partdata, HumNum nowtime);
		bool insertPartTimeSigs (pugi::xml_node timesig, GridPart& part);
		void insertPartMensurations(pugi::xml_node timesig, GridPart& part);
		void insertPartNames    (HumGrid& outdata, std::vector<MxmlPart>& partdata);
		bool checkForMensuration(pugi::xml_node timesig);
		pugi::xml_node convertTimeSigToHumdrum(pugi::xml_node timesig,
		                        HTp& token, int& staffindex);
		pugi::xml_node convertMensurationToHumdrum(pugi::xml_node timesig,
		                        HTp& token, int& staffindex);

		void addEvent          (GridSlice* slice, GridMeasure* outdata, MxmlEvent* event, HumNum nowtime);
		void fillEmpties       (GridPart* part, const char* string);
		void addSecondaryChordNotes (ostream& output, MxmlEvent* head, const std::string& recip);
		bool isInvisible       (MxmlEvent* event);
		int  addLyrics         (GridStaff* staff, MxmlEvent* event);
		int  addHarmony        (GridPart* oart, MxmlEvent* event, HumNum nowtime, int partindex);
		void addDynamic        (GridPart* part, MxmlEvent* event, int partindex);
		void addHairpinEnding  (GridPart* part, MxmlEvent* event, int partindex);
		int  addFiguredBass    (GridPart* part, MxmlEvent* event, HumNum nowtime, int partindex);
		void addTexts          (GridSlice* slice, GridMeasure* measure, int partindex,
		                        int staffindex, int voiceindex, MxmlEvent* event);
		void addText           (GridSlice* slice, GridMeasure* measure, int partindex,
		                        int staffindex, int voiceindex, pugi::xml_node node, bool force = false);
		void addTempos         (GridSlice* slice, GridMeasure* measure, int partindex,
		                        int staffindex, int voiceindex, MxmlEvent* event);
		void addTempo          (GridSlice* slice, GridMeasure* measure, int partindex,
		                        int staffindex, int voiceindex, pugi::xml_node node);
		void addBrackets       (GridSlice* slice, GridMeasure* measure, MxmlEvent* event, HumNum nowtime,
		                        int partindex);
		int         getHarmonyOffset(pugi::xml_node hnode);
		std::string getHarmonyString(pugi::xml_node hnode);
		std::string getDynamicString(pugi::xml_node element);
		std::string getDynamicsParameters(pugi::xml_node element);
		std::string getFiguredBassString(pugi::xml_node element);
		std::string getFiguredBassParameters(pugi::xml_node element);
		std::string convertFiguredBassNumber(const xml_node& figure);
		int         getFiguredBassDuration(xml_node fnode);
		std::string getHairpinString(pugi::xml_node element, int partindex);
		std::string cleanSpaces     (const std::string& input);
		void checkForDummyRests(MxmlMeasure* measure);
		void reindexVoices     (std::vector<MxmlPart>& partdata);
		void reindexMeasure    (MxmlMeasure* measure);
		void setSoftwareInfo   (pugi::xml_document& doc);
		std::string getSystemDecoration(pugi::xml_document& doc, HumGrid& grid, std::vector<std::string>& partids);
		void getChildrenVector (std::vector<pugi::xml_node>& children, pugi::xml_node parent);
		void insertPartTranspositions(pugi::xml_node transposition, GridPart& part);
		pugi::xml_node convertTranspositionToHumdrum(pugi::xml_node transpose, HTp& token, int& staffindex);
		void prepareRdfs       (std::vector<MxmlPart>& partdata);
		void printRdfs         (ostream& out);
		void printResult       (ostream& out, HumdrumFile& outfile);
		void addMeasureOneNumber(HumdrumFile& infile);
		bool isUsedHairpin     (pugi::xml_node hairpin, int partindex);

	public:

	static bool nodeType      (pugi::xml_node node, const char* testname);

	private:
		Options m_options;
		bool DebugQ;
		bool VoiceDebugQ;
		bool m_recipQ        = false;
		bool m_stemsQ        = false;
		int  m_slurabove     = 0;
		int  m_slurbelow     = 0;
		int  m_staffabove    = 0;
		int  m_staffbelow    = 0;
		char m_hasEditorial  = '\0';
		bool m_hasOrnamentsQ = false;
		int  m_maxstaff      = 0;
		std::vector<std::vector<std::string>> m_last_ottava_direction;
		std::vector<MusicXmlHarmonyInfo> offsetHarmony;
		std::vector<MusicXmlFiguredBassInfo> m_offsetFiguredBass;
		std::vector<string> m_stop_char;

		// RDF indications in **kern data:
		std::string  m_caesura_rdf;

		std::string m_software;
		std::string m_systemDecoration;

		std::vector<std::vector<pugi::xml_node>> m_current_dynamic;
		std::vector<std::vector<pugi::xml_node>> m_current_brackets;
		std::map<int, string> m_bracket_type_buffer;
		std::vector<std::vector<pugi::xml_node>> m_used_hairpins;
		std::vector<std::vector<pugi::xml_node>> m_current_figured_bass;
		std::vector<std::pair<int, pugi::xml_node>> m_current_text;
		std::vector<std::pair<int, pugi::xml_node>> m_current_tempo;

		bool m_hasTransposition = false;

		// m_forceRecipQ is used to force the display of the **recip spint
		// when a data line contains no notes or rests.  This is used for
		// harmony/dynamics side spines.
		bool m_forceRecipQ = false;

		// m_hasTremoloQ is used to run the tremolo tool.
		bool m_hasTremoloQ = false;

		// m_post_note_text is used to store interpretations that occur
		// before notes in the MusicXML data, but need to be moved after
		// the note in the Humdrum data.  The text will be stored and then
		// when note is processed, any text in this storage will be processed
		// index is a string: "part staff voice" with a vector list of strings
		// to process.
		std::map<std::string, vector<pugi::xml_node>> m_post_note_text;

};



class MyCoord {
	public:
		     MyCoord   (void) { clear(); }
		void clear   (void) { x = -1; y = -1; }
		bool isValid (void) { return ((x < 0) || (y < 0)) ? false : true; }
		int  x;
		int  y;
};

class MeasureInfo {
	public:
		MeasureInfo(void) { clear(); }
		void clear(void)  { num = seg = start = stop = -1;
			sclef.resize(0); skeysig.resize(0); skey.resize(0);
			stimesig.resize(0); smet.resize(0); stempo.resize(0);
			eclef.resize(0); ekeysig.resize(0); ekey.resize(0);
			etimesig.resize(0); emet.resize(0); etempo.resize(0);
			file = NULL;
		}
		void setTrackCount(int tcount) {
			sclef.resize(tcount+1);
			skeysig.resize(tcount+1);
			skey.resize(tcount+1);
			stimesig.resize(tcount+1);
			smet.resize(tcount+1);
			stempo.resize(tcount+1);
			eclef.resize(tcount+1);
			ekeysig.resize(tcount+1);
			ekey.resize(tcount+1);
			etimesig.resize(tcount+1);
			emet.resize(tcount+1);
			etempo.resize(tcount+1);
			int i;
			for (i=0; i<tcount+1; i++) {
				sclef[i].clear();
				skeysig[i].clear();
				skey[i].clear();
				stimesig[i].clear();
				smet[i].clear();
				stempo[i].clear();
				eclef[i].clear();
				ekeysig[i].clear();
				ekey[i].clear();
				etimesig[i].clear();
				emet[i].clear();
				etempo[i].clear();
			}
			tracks = tcount;
		}
		int num;          // measure number
		std::string stopStyle;  // styling for end of last measure
		std::string startStyle; // styling for start of first measure
		int seg;          // measure segment
		int start;        // starting line of segment
		int stop;         // ending line of segment
		int tracks;       // number of primary tracks in file.
		HumdrumFile* file;

		// musical settings at start of measure
		std::vector<MyCoord> sclef;     // starting clef of segment
		std::vector<MyCoord> skeysig;   // starting keysig of segment
		std::vector<MyCoord> skey;      // starting key of segment
		std::vector<MyCoord> stimesig;  // starting timesig of segment
		std::vector<MyCoord> smet;      // starting met of segment
		std::vector<MyCoord> stempo;    // starting tempo of segment

		// musical settings at start of measure
		std::vector<MyCoord> eclef;     // ending clef    of segment
		std::vector<MyCoord> ekeysig;   // ending keysig  of segment
		std::vector<MyCoord> ekey;      // ending key     of segment
		std::vector<MyCoord> etimesig;  // ending timesig of segment
		std::vector<MyCoord> emet;      // ending met     of segment
		std::vector<MyCoord> etempo;    // ending tempo   of segment
};



class Tool_myank : public HumTool {
	public:
		         Tool_myank            (void);
		        ~Tool_myank            () {};

		bool     run                   (HumdrumFileSet& infiles);
		bool     run                   (HumdrumFile& infile);
		bool     run                   (const std::string& indata, std::ostream& out);
		bool     run                   (HumdrumFile& infile, std::ostream& out);

	protected:
		void      initialize            (HumdrumFile& infile);
		void      example              (void);
		void      usage                (const std::string& command);
		void      myank                (HumdrumFile& infile,
		                                std::vector<MeasureInfo>& outmeasure);
		void      removeDollarsFromString(std::string& buffer, int maxx);
		void      processFieldEntry    (std::vector<MeasureInfo>& field,
		                                const std::string& str,
		                                HumdrumFile& infile, int maxmeasure,
		                                std::vector<MeasureInfo>& inmeasures,
		                                std::vector<int>& inmap);
		void      expandMeasureOutList (std::vector<MeasureInfo>& measureout,
		                                std::vector<MeasureInfo>& measurein,
		                                HumdrumFile& infile, const std::string& optionstring);
		void      getMeasureStartStop  (std::vector<MeasureInfo>& measurelist,
		                                HumdrumFile& infile);
		void      printEnding          (HumdrumFile& infile, int lastline, int adjlin);
		void      printStarting        (HumdrumFile& infile);
		void      reconcileSpineBoundary(HumdrumFile& infile, int index1, int index2);
		void      reconcileStartingPosition(HumdrumFile& infile, int index2);
		void      printJoinLine        (std::vector<int>& splits, int index, int count);
		void      printInvisibleMeasure(HumdrumFile& infile, int line);
		void      fillGlobalDefaults   (HumdrumFile& infile,
		                                std::vector<MeasureInfo>& measurein,
		                                std::vector<int>& inmap);
		void      adjustGlobalInterpretations(HumdrumFile& infile, int ii,
		                                std::vector<MeasureInfo>& outmeasures,
		                                int index);
		void      adjustGlobalInterpretationsStart(HumdrumFile& infile, int ii,
		                                std::vector<MeasureInfo>& outmeasures,
		                                int index);
		void      getMarkString        (std::ostream& out, HumdrumFile& infile);
		void      printDoubleBarline   (HumdrumFile& infile, int line);
		void      insertZerothMeasure  (std::vector<MeasureInfo>& measurelist,
		                                HumdrumFile& infile);
		void      getMetStates         (std::vector<std::vector<MyCoord> >& metstates,
		                                HumdrumFile& infile);
		MyCoord   getLocalMetInfo      (HumdrumFile& infile, int row, int track);
		int       atEndOfFile          (HumdrumFile& infile, int line);
		void      processFile          (HumdrumFile& infile);
		int       getSectionCount      (HumdrumFile& infile);
		void      getSectionString     (std::string& sstring, HumdrumFile& infile,
		                                int sec);
		void      collapseSpines       (HumdrumFile& infile, int line);
		void      printMeasureStart    (HumdrumFile& infile, int line, const std::string& style);
		std::string expandMultipliers  (const std::string& inputstring);

		std::vector<int> analyzeBarNumbers  (HumdrumFile& infile);
		int         getBarNumberForLineNumber(int lineNumber);
		int         getStartLineNumber (void);
		int         getEndLineNumber   (void);
		void        printDataLine      (HLp line, bool& startLineHandled, const std::vector<int>& lastLineResolvedTokenLineIndex, const std::vector<HumNum>& lastLineDurationsFromNoteStart);

	private:
		int    m_debugQ      = 0;             // used with --debug option
		// int    inputlist     = 0;             // used with --inlist option
		int    m_inlistQ     = 0;             // used with --inlist option
		int    m_outlistQ    = 0;             // used with --outlist option
		int    m_verboseQ    = 0;             // used with -v option
		int    m_invisibleQ  = 1;             // used with --visible option
		int    m_maxQ        = 0;             // used with --max option
		int    m_minQ        = 0;             // used with --min option
		int    m_instrumentQ = 0;             // used with -I option
		int    m_nolastbarQ  = 0;             // used with -B option
		int    m_markQ       = 0;             // used with --mark option
		int    m_doubleQ     = 0;             // used with --mdsep option
		int    m_barnumtextQ = 0;             // used with -T option
		int    m_section     = 0;             // used with --section option
		int    m_sectionCountQ = 0;           // used with --section-count option
		std::vector<MeasureInfo> m_measureOutList; // used with -m option
		std::vector<MeasureInfo> m_measureInList;  // used with -m option
		std::vector<std::vector<MyCoord> > m_metstates;

		std::string m_lineRange;              // used with -l option
		std::vector<int> m_barNumbersPerLine;      // used with -l option
		bool m_hideStarting;                  // used with --hide-starting option
		bool m_hideEnding;                    // used with --hide-ending option

};


class Tool_nproof : public HumTool {

	public:
		         Tool_nproof        (void);
		        ~Tool_nproof        () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

		void     checkForBlankLines(HumdrumFile& infile);
		void     checkInstrumentInformation(HumdrumFile& infile);
		void     checkKeyInformation(HumdrumFile& infile);
		void     checkSpineTerminations(HumdrumFile& infile);
		void     checkForValidInstrumentCode(HTp token, std::vector<std::pair<std::string, std::string>>& instrumentList);
		void     checkReferenceRecords(HumdrumFile& infile);

	protected:
		void     initialize        (void);
		void     processFile       (HumdrumFile& infile);

	private:
		int m_errorCount = 0;
		std::string m_errorList;
		std::string m_errorHtml;

		bool m_noblankQ       = false;
		bool m_noinstrumentQ  = false;
		bool m_nokeyQ         = false;
		bool m_noreferenceQ   = false;
		bool m_noterminationQ = false;

		bool m_fileQ          = false;
		bool m_rawQ           = false;

};


class Tool_ordergps : public HumTool {
	public:
		      Tool_ordergps  (void);
		     ~Tool_ordergps  () {};

		bool  run            (HumdrumFileSet& infiles);
		bool  run            (HumdrumFile& infile);
		bool  run            (const std::string& indata, std::ostream& out);
		bool  run            (HumdrumFile& infile, std::ostream& out);

	protected:
		void  initialize     (void);
		void  processFile    (HumdrumFile& infile);
		void  printStaffLine (HumdrumFile& infile);
		void  printFile      (HumdrumFile& infile, int gindex, int pindex, int sindex);
		void  printFileTop   (HumdrumFile& infile, int gindex, int pindex, int sindex);

	private:
		bool m_emptyQ   = false;
		bool m_fileQ    = false;
		bool m_listQ    = false;
		bool m_problemQ = false;
		bool m_reverseQ = false;
		bool m_staffQ   = false;
		bool m_topQ     = false;

};


class Tool_pbar : public HumTool {
	public:
		            Tool_pbar        (void);
		           ~Tool_pbar        () {};

		bool        run               (HumdrumFileSet& infiles);
		bool        run               (HumdrumFile& infile);
		bool        run               (const std::string& indata, std::ostream& out);
		bool        run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void        processFile       (HumdrumFile& infile);
		void        initialize        (void);
		void        processSpine      (HTp spineStart);
		void        printDataLine                   (HumdrumFile& infile, int index);
		void        printLocalCommentLine           (HumdrumFile& infile, int index);
		void        addBarLineToFollowingNoteOrRest (HTp token);
		void        printInvisibleBarlines          (HumdrumFile& infile, int index);
		void        printBarLine                    (HumdrumFile& infile, int index);

	private:
		bool        m_invisibleQ = false;   // used with -i option

};



class Tool_pccount : public HumTool {
	public:
		      Tool_pccount              (void);
		     ~Tool_pccount              () {};

		bool  run                       (HumdrumFileSet& infiles);
		bool  run                       (HumdrumFile& infile);
		bool  run                       (const std::string& indata, std::ostream& out);
		bool  run                       (HumdrumFile& infile, std::ostream& out);

	protected:
		void   initialize               (HumdrumFile& infile);
		void   processFile              (HumdrumFile& infile);
		void   initializePartInfo       (HumdrumFile& infile);
		void   addCounts                (HTp sstart, HTp send);
		void   countPitches             (HumdrumFile& infile);
		void   printHumdrumTable        (void);
		void   printPitchClassList      (void);
		void   printVegaLiteJsonTemplate(const std::string& datavariable, HumdrumFile& infile);
		void   printVegaLiteJsonData    (void);
		void   printVoiceList           (void);
		void   printReverseVoiceList    (void);
		void   printColorList           (void);
		std::string getPitchClassString (int b40);
		void   printVegaLiteScript      (const std::string& jsonvar,
		                                 const std::string& target,
		                                 const std::string& datavar,
		                                 HumdrumFile& infile);
		void   printVegaLiteHtml        (const std::string& jsonvar,
		                                 const std::string& target,
		                                 const std::string& datavar,
		                                 HumdrumFile& infile);
		void   printVegaLitePage        (const std::string& jsonvar,
		                                 const std::string& target,
		                                 const std::string& datavar,
		                                 HumdrumFile& infile);
		std::string getFinal            (HumdrumFile& infile);
		double  getPercent              (const std::string& pitchclass);
		int     getCount                (const std::string& pitchclass);
		void    setFactorMaximum        (void);
		void    setFactorNormalize      (void);

	private:
		std::vector<int>               m_rkern;
		std::vector<int>               m_parttracks;
		std::vector<std::string>       m_names;
		std::vector<std::string>       m_abbreviations;
		std::vector<std::vector<double>> m_counts;
		bool m_attack       = false;
		bool m_full         = false;
		bool m_doublefull   = false;
		bool m_normalize    = false;
		bool m_maximum      = false;
		bool m_template     = false;
		bool m_data         = false;
		bool m_script       = false;
		bool m_html         = false;
		bool m_page         = false;
		int  m_width        = 500;
		double m_ratio      = 0.67;
		bool m_key          = true;
		double m_factor     = 1.0;
		int m_maxpc         = 0;
		std::string m_title = "";
		std::string m_id    = "id";
		std::map<std::string, std::string> m_vcolor;

};





class Tool_periodicity : public HumTool {
	public:
		         Tool_periodicity   (void);
		        ~Tool_periodicity   () {};

		bool     run                (HumdrumFileSet& infiles);
		bool     run                (HumdrumFile& infile);
		bool     run                (const std::string& indata, std::ostream& out);
		bool     run                (HumdrumFile& infile, std::ostream& out);

	protected:
		void     initialize         (HumdrumFile& infile);
		void     processFile        (HumdrumFile& infile);
		void     fillAttackGrids    (HumdrumFile& infile, std::vector<std::vector<double>>& grids, HumNum minrhy);
		void     printAttackGrid    (std::ostream& out, HumdrumFile& infile, std::vector<std::vector<double>>& grids, HumNum minrhy);
		void     doAnalysis         (std::vector<std::vector<double>>& analysis, int level, std::vector<double>& grid);
		void     doPeriodicityAnalysis(std::vector<std::vector<double>> & analysis, std::vector<double>& grid, HumNum minrhy);
		void     printPeriodicityAnalysis(std::ostream& out, std::vector<std::vector<double>>& analysis);
		void     printSvgAnalysis(std::ostream& out, std::vector<std::vector<double>>& analysis, HumNum minrhy);
		void     getColorMapping(double input, double& hue, double& saturation, double& lightness);

	private:

};


class Tool_phrase : public HumTool {
	public:
		     Tool_phrase          (void);
		    ~Tool_phrase          () {};

		bool  run                 (HumdrumFileSet& infiles);
		bool  run                 (HumdrumFile& infile);
		bool  run                 (const std::string& indata, std::ostream& out);
		bool  run                 (HumdrumFile& infile, std::ostream& out);

	protected:
		void  analyzeSpineByRests (int index);
		void  analyzeSpineByPhrase(int index);
		void  initialize          (HumdrumFile& infile);
		void  prepareAnalysis     (HumdrumFile& infile);
		void  addAverageLines     (HumdrumFile& infile);
		bool  hasPhraseMarks      (HTp start);
		void  removePhraseMarks   (HTp start);

	private:
		std::vector<std::vector<std::string>>    m_results;
		std::vector<HTp>               m_starts;
		HumdrumFile               m_infile;
		std::vector<int>               m_pcount;
		std::vector<HumNum>            m_psum;
		bool                      m_markQ;
		bool                      m_removeQ;
		bool                      m_remove2Q;
		bool                      m_averageQ;
		std::string               m_color;

};



class Tool_pline : public HumTool {
	public:
		         Tool_pline        (void);
		        ~Tool_pline        () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);


	protected:
		void     initialize        (void);
		void     processFile       (HumdrumFile& infile);
		void     getPlineInterpretations(HumdrumFile& infile, std::vector<HTp>& tokens);
		void     plineToColor      (HumdrumFile& infile, std::vector<HTp>& tokens);
		void     markRests         (HumdrumFile& infile);
		void     markSpineRests    (HTp spineStop);
		void     fillLineInfo      (HumdrumFile& infile, std::vector<std::vector<int>>& lineInfo);

	private:
		bool     m_colorQ   = false;  // used with -c option
		// bool     m_overlapQ = false;  // used with -o option

		std::vector<std::string> m_colors;
		std::vector<HTp> m_ptokens;
		std::vector<std::vector<int>> m_lineInfo;


};


class Tool_pnum : public HumTool {
	public:
		      Tool_pnum               (void);
		     ~Tool_pnum               () {};

		bool  run                     (HumdrumFileSet& infiles);
		bool  run                     (HumdrumFile& infile);
		bool  run                     (const std::string& indata, std::ostream& out);
		bool  run                     (HumdrumFile& infile, std::ostream& out);

	protected:
		void  initialize              (HumdrumFile& infile);
		void  processFile             (HumdrumFile& infile);
		std::string convertSubtokenToBase(const std::string& text);
		void  convertTokenToBase      (HTp token);

	private:
		int  m_base = 12;
		int  m_midiQ;
		bool m_durationQ;
		bool m_classQ;
		bool m_octaveQ;
		bool m_attacksQ;
		std::string m_rest;
		bool m_restQ;

};




class _VoiceInfo {
	public:
		std::vector<std::vector<double>>   diatonic;
		std::vector<double>                midibins;
		std::string                        name;      // name for instrument name of spine
		std::string                        abbr;      // abbreviation for instrument name of spine
		int                                track;     // track number for spine
		bool                               kernQ;     // is spine a **kern spine?
		double                             hpos;      // horiz. position on system for pitch range data for spine
		std::vector<int>                   diafinal;  // finalis note diatonic pitch (4=middle-C octave)
		std::vector<int>                   accfinal;  // finalis note accidental (0 = natural)
		std::vector<std::string>           namfinal;  // name of voice for finalis note (for "all" display)
		int                                index = -1;

	public:
		                _VoiceInfo        (void);
		void            clear             (void);
		std::ostream&   print             (std::ostream& out);

};



class Tool_prange : public HumTool {
	public:
		         Tool_prange       (void);
		        ~Tool_prange       () {};

		bool        run               (HumdrumFileSet& infiles);
		bool        run               (HumdrumFile& infile);
		bool        run               (const std::string& indata, std::ostream& out);
		bool        run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void        processFile         (HumdrumFile& infile);
		void        initialize          (void);

		void        mergeAllVoiceInfo           (std::vector<_VoiceInfo>& voiceInfo);
		void        getVoiceInfo                (std::vector<_VoiceInfo>& voiceInfo, HumdrumFile& infile);
		std::string getHand                     (HTp sstart);
		void        fillHistograms              (std::vector<_VoiceInfo>& voiceInfo, HumdrumFile& infile);
		void        printFilenameBase           (std::ostream& out, const std::string& filename);
		void        printReferenceRecords       (std::ostream& out, HumdrumFile& infile);
		void        printScoreEncodedText       (std::ostream& out, const std::string& strang);
		void        printXmlEncodedText         (std::ostream& out, const std::string& strang);
		void        printScoreFile              (std::ostream& out, std::vector<_VoiceInfo>& voiceInfo, HumdrumFile& infile);
		void        printKeySigCompression      (std::ostream& out, int keysig, int extra);
		void        assignHorizontalPosition    (std::vector<_VoiceInfo>& voiceInfo, int minval, int maxval);
		int         getKeySignature             (HumdrumFile& infile);
		void        printScoreVoice             (std::ostream& out, _VoiceInfo& voiceInfo, double maxvalue);
		void        printDiatonicPitchName      (std::ostream& out, int base7, int acc);
		std::string getDiatonicPitchName        (int base7, int acc);
		void        printHtmlStringEncodeSimple (std::ostream& out, const std::string& strang);
		std::string getNoteTitle                (double value, int diatonic, int acc);
		int         getDiatonicInterval         (int note1, int note2);
		int         getTopQuartile              (std::vector<double>& midibins);
		int         getBottomQuartile           (std::vector<double>& midibins);
		double      getMaxValue                 (std::vector<std::vector<double>>& bins);
		double      getVpos                     (double base7);
		int         getStaffBase7               (int base7);
		int         getMaxDiatonicIndex         (std::vector<std::vector<double>>& diatonic);
		int         getMinDiatonicIndex         (std::vector<std::vector<double>>& diatonic);
		int         getMinDiatonicAcc           (std::vector<std::vector<double>>& diatonic, int index);
		int         getMaxDiatonicAcc           (std::vector<std::vector<double>>& diatonic, int index);
		std::string getTitle                    (void);
		void        clearHistograms             (std::vector<std::vector<double> >& bins, int start);
		void        printAnalysis               (std::ostream& out, std::vector<double>& midibins);
		int         getMedian12                 (std::vector<double>& midibins);
		double      getMean12                   (std::vector<double>& midibins);
		int         getTessitura                (std::vector<double>& midibins);
		double      countNotesInRange           (std::vector<double>& midibins, int low, int high);
		void        printPercentile             (std::ostream& out, std::vector<double>& midibins, double percentile);
		void        getRange                    (int& rangeL, int& rangeH, const std::string& rangestring);
		void        mergeFinals                 (std::vector<_VoiceInfo>& voiceInfo,
		                                         std::vector<std::vector<int>>& diafinal,
		                                         std::vector<std::vector<int>>& accfinal);
		void        getInstrumentNames          (std::vector<std::string>& nameByTrack,
		                                         std::vector<int>& kernSpines, HumdrumFile& infile);
		void        printEmbeddedScore          (std::ostream& out, std::stringstream& scoredata, HumdrumFile& infile);
		void        prepareRefmap               (HumdrumFile& infile);
		int         getMaxStaffPosition         (std::vector<_VoiceInfo>& voiceinfo);
		int         getPrangeId                 (HumdrumFile& infile);
		void        processStrandNotes          (HTp sstart, HTp send,
		                                         std::vector<std::vector<std::pair<HTp, int>>>& trackInfo);
		void        fillMidiInfo                (HumdrumFile& infile);
		void        doExtremaMarkup             (HumdrumFile& infile);
		void        applyMarkup                 (std::vector<std::pair<HTp, int>>& notelist,
		                                         const std::string& mark);

	private:

		bool m_accQ         = false; // for --acc option
		bool m_addFractionQ = false; // for --fraction option
		bool m_allQ         = false; // for --all option
		bool m_debugQ       = false; // for --debug option
		bool m_defineQ      = false; // for --score option (use text macro)
		bool m_diatonicQ    = false; // for --diatonic option
		bool m_durationQ    = false; // for --duration option
		bool m_embedQ       = false; // for --embed option
		bool m_fillOnlyQ    = false; // for --fill option
		bool m_finalisQ     = false; // for --finalis option
		bool m_hoverQ       = false; // for --hover option
		bool m_instrumentQ  = false; // for --instrument option
		bool m_keyQ         = true;  // for --no-key option
		bool m_listQ        = false;
		bool m_localQ       = false; // for --local-maximum option
		bool m_normQ        = false; // for --norm option
		bool m_notitleQ     = false; // for --no-title option
		bool m_percentileQ  = false; // for --percentile option
		bool m_pitchQ       = false; // for --pitch option
		bool m_printQ       = false; // for --print option
		bool m_quartileQ    = false; // for --quartile option
		bool m_rangeQ       = false; // for --range option
		bool m_reverseQ     = false; // for --reverse option
		bool m_scoreQ       = false; // for --score option
		bool m_titleQ       = false; // for --title option
		bool m_extremaQ     = false; // for --extrema option

		std::string m_highMark = "🌸";
		std::string m_lowMark  = "🟢";

		double m_percentile = 50.0;  // for --percentile option
		std::string m_title;         // for --title option

		int m_rangeL;                // for --range option
		int m_rangeH;                // for --range option

		std::map<std::string, std::string> m_refmap;

		//   track       >midi       >tokens        <token, subtoken>
		std::vector<std::vector<std::vector<std::pair<HTp, int>>>> m_trackMidi;

		// m_trackToKernIndex: mapping from track to **kern index
		std::vector<int> m_trackToKernIndex;

};


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



class Tool_restfill : public HumTool {
	public:
		         Tool_restfill         (void);
		        ~Tool_restfill         () {};

		bool        run                (HumdrumFileSet& infiles);
		bool        run                (HumdrumFile& infile);
		bool        run                (const std::string& indata, std::ostream& out);
		bool        run                (HumdrumFile& infile, std::ostream& out);

	protected:
		void        processFile        (HumdrumFile& infile);
		void        initialize         (void);
		bool        hasBlankMeasure    (HTp start);
		void        fillInRests        (HTp start);
		void        addRest            (HTp cell, HumNum duration);
		HumNum      getNextTime        (HTp token);

	private:
		bool        m_hiddenQ  = false;
		std::string m_exinterp = "**kern";

};


class Tool_rid : public HumTool {
	public:
		         Tool_rid          (void);
		        ~Tool_rid          () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void     processFile       (HumdrumFile& infile);
		void     initialize        (void);

	private:

		// User interface variables:
		int      option_D = 0;   // used with -D option
		int      option_d = 0;   // used with -d option
		int      option_G = 0;   // used with -G option
		int      option_g = 0;   // used with -g option
		int      option_I = 0;   // used with -I option
		int      option_i = 0;   // used with -i option
		int      option_L = 0;   // used with -L option
		int      option_l = 0;   // used with -l option
		int      option_T = 0;   // used with -T option
		int      option_U = 0;   // used with -U and -u option

		int      option_M = 0;   // used with -M option
		int      option_C = 0;   // used with -C option
		int      option_c = 0;   // used with -c option
		int      option_k = 0;   // used with -k option
		int      option_V = 0;   // used with -V option

};


class Tool_rphrase : public HumTool {
	public:

	class VoiceInfo {
		public:
			std::string name;
			std::vector<double> restsBefore;
			std::vector<double> phraseDurs;
			std::vector<int>    barStarts;
			std::vector<HTp>    phraseStartToks;
	};

		         Tool_rphrase      (void);
		        ~Tool_rphrase      () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);
		void     finally           (void);

	protected:
		void     initialize        (void);
		void     processFile       (HumdrumFile& infile);
		void     fillVoiceInfo     (std::vector<Tool_rphrase::VoiceInfo>& voiceInfo, std::vector<HTp>& kstarts, HumdrumFile& infile);
		void     fillVoiceInfo     (Tool_rphrase::VoiceInfo& voiceInfo, HTp& kstart, HumdrumFile& infile);
		void     fillCompositeInfo  (Tool_rphrase::VoiceInfo& collapseInfo, HumdrumFile& infile);
		void     printVoiceInfo    (std::vector<Tool_rphrase::VoiceInfo>& voiceInfo);
		void     printVoiceInfo    (Tool_rphrase::VoiceInfo& voiceInfo);

		void     printEmbeddedVoiceInfo(std::vector<Tool_rphrase::VoiceInfo>& voiceInfo, Tool_rphrase::VoiceInfo& collapseInfo, HumdrumFile& infile);
		void     printEmbeddedIndividualVoiceInfo(Tool_rphrase::VoiceInfo& voiceInfo, HumdrumFile& infile);
		void     printEmbeddedCompositeInfo(Tool_rphrase::VoiceInfo& compositeInfo, HumdrumFile& infile);

		void     getCompositeStates(std::vector<int>& noteStates, HumdrumFile& infile);
		std::string getCompositeLabel(HumdrumFile& infile);
		void     markPhraseStartsInScore(HumdrumFile& infile, Tool_rphrase::VoiceInfo& voiceInfo);
		void     markCompositePhraseStartsInScore(HumdrumFile& infile, Tool_rphrase::VoiceInfo& collapseInfo);
		void     outputMarkedFile  (HumdrumFile& infile, std::vector<Tool_rphrase::VoiceInfo>& voiceInfo,
		                            Tool_rphrase::VoiceInfo& compositeInfo);
		void     printDataLine     (HumdrumFile& infile, int index);
		void     markLongaDurations(HumdrumFile& infile);
		std::string getVoiceInfo(HumdrumFile& infile);
		void     printEmbeddedVoiceInfoSummary(std::vector<Tool_rphrase::VoiceInfo>& voiceInfo, HumdrumFile& infile);
		double   twoDigitRound(double input);
		void     printHyperlink(const std::string& urlType);

	private:
		bool        m_averageQ        = false; // for -a option
		bool        m_allAverageQ     = false; // for -A option
		bool        m_breathQ         = true;  // for -B option
		bool        m_barlineQ        = false; // for -m option
		bool        m_compositeQ      = false; // for -c option
		bool        m_longaQ          = false; // for -l option
		bool        m_filenameQ       = false; // for -f option
		bool        m_fullFilenameQ   = false; // for -F option
		std::string m_filename;                // for -f or -F option
		bool        m_sortQ           = false; // for -s option
		bool        m_reverseSortQ    = false; // for -S option
		int         m_pcount          = 0;     // for -a option
		double      m_sum             = 0.0;   // for -a option
		int         m_pcountComposite = 0;     // for -c option
		double      m_sumComposite    = 0.0;   // for -c option
		bool        m_markQ           = false; // for --mark option
		double      m_durUnit         = 2.0;   // for -d option
		bool        m_infoQ           = false; // for -i option (when --mark is active)
		bool        m_squeezeQ        = false; // for -z option
		bool        m_closeQ          = false; // for --close option
		std::string m_urlType;                 // for -u option

		int         m_line = 1;
		std::string m_voiceLengthColor     = "crimson";
		std::string m_compositeLengthColor = "limegreen";

};


class Tool_ruthfix : public HumTool {
	public:
		         Tool_ruthfix      (void);
		        ~Tool_ruthfix      () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const string& indata, ostream& out);
		bool     run               (HumdrumFile& infile, ostream& out);

	protected:
		void    insertCrossBarTies (HumdrumFile& infile);
		void    insertCrossBarTies (HumdrumFile& infile, int strand);
		void    createTiedNote     (HTp left, HTp right);

};


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


class Tool_satb2gs : public HumTool {
	public:
		         Tool_satb2gs      (void);
		        ~Tool_satb2gs      () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void    processFile        (HumdrumFile& infile);
		void    initialize         (void);
		void    getTrackInfo       (std::vector<std::vector<int>>& tracks,
		                            HumdrumFile& infile);

		void    printTerminatorLine(std::vector<std::vector<int>>& tracks);
		int     getNewTrackCount   (std::vector<std::vector<int>>& tracks);
		void    printRegularLine   (HumdrumFile& infile, int line,
		                            std::vector<std::vector<int>>& tracks);
		void    printSpineMergeLine(std::vector<std::vector<int>>& tracks);
		void    printSpineSplitLine(std::vector<std::vector<int>>& tracks);
		void    printHeaderLine    (HumdrumFile& infile, int line,
		                            std::vector<std::vector<int>>& tracks);
		bool    validateHeader     (HumdrumFile& infile);
		std::vector<HTp> getClefs       (HumdrumFile& infile, int line);

};


class Tool_scordatura : public HumTool {
	public:
		         Tool_scordatura   (void);
		        ~Tool_scordatura   () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void     processFile       (HumdrumFile& infile);
		void     initialize        (void);
		void     getScordaturaRdfs (std::vector<HTp>& rdfs, HumdrumFile& infile);
		void     processScordatura (HumdrumFile& infile, HTp reference);
		void     processScordaturas(HumdrumFile& infile, std::vector<HTp>& rdfs);
		void     flipScordaturaInfo(HTp reference, int diatonic, int chromatic);
		void     transposeStrand   (HTp sstart, HTp sstop, const std::string& marker);
		void     transposeChord    (HTp token, const std::string& marker);
		std::string transposeNote     (const std::string& note);
		void     transposeMarker   (HumdrumFile& infile, const std::string& marker, int diatonic, int chromatic);
		std::set<int> parsePitches(const std::string& input);
		void     markPitches       (HumdrumFile& infile);
		void     markPitches       (HTp sstart, HTp sstop);
		void     markPitches       (HTp token);
		void     addMarkerRdf      (HumdrumFile& infile);
		void     prepareTranspositionInterval(void);

	private:
		bool           m_writtenQ    = false;
		bool           m_soundingQ   = false;
		bool           m_modifiedQ   = false;
		bool           m_IQ          = false;  // true: enbed marker in sounding score
		std::string    m_transposition;
		std::string    m_color;
		std::string    m_marker;
		std::set<int>  m_pitches;
		HumTransposer  m_transposer;
		int            m_diatonic;
		int            m_chromatic;
		std::string    m_interval;
		bool           m_cd;
		std::string    m_string;

};


class Tool_semitones : public HumTool {
	public:
		      Tool_semitones   (void);
		     ~Tool_semitones   () {};

		bool  run              (HumdrumFileSet& infiles);
		bool  run              (HumdrumFile& infile);
		bool  run              (const std::string& indata, std::ostream& out);
		bool  run              (HumdrumFile& infile, std::ostream& out);

	protected:
		void        processFile(HumdrumFile& infile);
		void        initialize(void);
		void        analyzeLine(HumdrumFile& infile, int line);
		int         processKernSpines(HumdrumFile& infile, int line, int start, int kspine);
		void        printTokens(const std::string& value, int count);
		std::string getTwelveToneIntervalString(HTp token);
		std::string getNextNoteAttack(HTp token);
		void        markInterval(HTp token);
		HTp         markNote(HTp token, bool markQ);
		void        addMarker(HTp token);
		void        showCount(void);
		int         filterData(HTp token);
		std::vector<HTp> getTieGroup(HTp token);
		HTp         getNextNote(HTp token);
		bool        hasTieContinue(const std::string& value);

	private:

		bool        m_cdataQ      = false; // used **cdata (to display in VHV notation)
		bool        m_downQ       = false; // mark/count notes in downward interval
		bool        m_firstQ      = false; // mark only first note in interval
		bool        m_leapQ       = false; // mark/count notes in leap motion
		bool        m_midiQ       = false; // give the MIDI note number rather than inteval.
		bool        m_noanalysisQ = false; // do not print analysis spines
		bool        m_noinputQ    = false; // do not print input data
		bool        m_nomarkQ     = false; // do not mark notes (just count intervals)
		bool        m_norestsQ    = false; // ignore rests
		bool        m_notiesQ     = false; // do not mark secondary tied notes
		bool        m_pcQ         = false; // give pitch class rather than MIDI note num.
		bool        m_repeatQ     = false; // make/count notes that repeat
		bool        m_secondQ     = false; // mark only second note in interval
		bool        m_stepQ       = false; // mark/count notes in stepwise motion
		bool        m_upQ         = false; // mark/count notes in upward interval
      bool        m_count       = false; // count the number of intervals being marked

		int         m_markCount = 0;
		int         m_leap      = 3;

      std::string m_marker  = "@";
		std::string m_color   = "red";
		std::string m_include;
		std::string m_exclude;

};



class Tool_shed : public HumTool {
	public:
		         Tool_shed       (void);
		        ~Tool_shed       () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void    processFile                      (HumdrumFile& infile);
		void    processExpression                (HumdrumFile& infile);
		void    searchAndReplaceInterpretation   (HumdrumFile& infile);
		void    searchAndReplaceExinterp         (HumdrumFile& infile);
		void    searchAndReplaceData             (HumdrumFile& infile);
		void    searchAndReplaceBarline          (HumdrumFile& infile);
		void    searchAndReplaceLocalComment     (HumdrumFile& infile);
		void    searchAndReplaceGlobalComment    (HumdrumFile& infile);
		void    searchAndReplaceReferenceRecords (HumdrumFile& infile);
		void    searchAndReplaceReferenceKeys    (HumdrumFile& infile);
		void    searchAndReplaceReferenceValues  (HumdrumFile& infile);

		void    initialize         (void);
		void    initializeSegment  (HumdrumFile& infile);
		bool    isValid            (HTp token);
		bool    isValidDataType    (HTp token);
		bool    isValidSpine       (HTp token);
		std::vector<std::string> addToExInterpList(void);
		void    parseExpression    (const std::string& value);
		void    prepareSearch      (int index);
		std::string getExInterp    (const std::string& value);

	private:
		std::vector<std::string> m_searches;  // search strings
		std::vector<std::string> m_replaces;  // replace strings
		std::vector<std::string> m_options;   // search options

		std::string m_search;
		std::string m_replace;
		std::string m_option;

		bool m_data           = true;  // process data
		bool m_barline        = false; // process barlines
		bool m_exinterp       = false; // process exclusive interpretations
		bool m_interpretation = false; // process interpretations
		bool m_localcomment   = false; // process local comments
		bool m_globalcomment  = false; // process global comments
		bool m_reference      = false; // process reference records
		bool m_referencekey   = false; // process reference records keys
		bool m_referencevalue = false; // process reference records values
		std::string m_xInterp; // used with -x option
		std::string m_yInterp; // used with -y option
		std::string m_zInterp; // used with -z option

		bool m_modified       = false;

		// list of exclusive interpretations to process
		std::vector<std::string> m_exinterps;
		std::string m_exclusion;

		std::vector<bool> m_spines; // usar with -s option
		std::string m_grepoptions;

};


class Tool_sic : public HumTool {
	public:
		         Tool_sic       (void);
		        ~Tool_sic       () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void     processFile       (HumdrumFile& infile);
		void     initialize        (void);
		void     insertOriginalToken(HTp sictok);
		void     insertSubstitutionToken(HTp sictok);
		HTp      getTargetToken     (HTp stok);
		void     addVerboseParameter(HTp token);
		void     removeVerboseParameter(HTp token);

	private:
		bool     m_substituteQ = false;
		bool     m_originalQ   = false;
		bool     m_removeQ     = false;
		bool     m_verboseQ    = false;
		bool     m_quietQ      = false;
		bool     m_modifiedQ   = false;

};


class MeasureData {
	public:
		            MeasureData               (void);
		            MeasureData               (HumdrumFile& infile,
		                                       int startline,int stopline);
		            MeasureData               (HumdrumFile* infile,
		                                      int startline,int stopline);
		           ~MeasureData               ();
		void        setOwner                  (HumdrumFile* infile);
		void        setOwner                  (HumdrumFile& infile);
		void        setStartLine              (int startline);
		void        setStopLine               (int stopline);
		int         getStartLine              (void);
		int         getStopLine               (void);
		void        clear                     (void);
		std::vector<double>& getHistogram7pc (void);
		void        generateNoteHistogram     (void);
		double      getSum7pc                 (void);
		double      getStartTime              (void);
		double      getStopTime               (void);
		double      getDuration               (void);
		int         getMeasure                (void);
		std::string getQoff                   (void);
		std::string getQon                    (void);
		double      getScoreDuration          (void);

	private:
		HumdrumFile*        m_owner       = NULL;
		int                 m_startline   = -1;
		int                 m_stopline    = -1;
		std::vector<double> m_hist7pc;
		double              m_sum7pc      = 0.0;
};



class MeasureDataSet {
	public:
		             MeasureDataSet   (void);
		             MeasureDataSet   (HumdrumFile& infile);
		            ~MeasureDataSet   ();

		void         clear            (void);
		int          parse            (HumdrumFile& infile);
		MeasureData& operator[]       (int index);
		int          size             (void) { return (int)m_data.size(); }
		double       getScoreDuration (void);

	private:
		std::vector<MeasureData*> m_data;
};



class MeasureComparison {
	public:
		MeasureComparison();
		MeasureComparison(MeasureData& data1, MeasureData& data2);
		MeasureComparison(MeasureData* data1, MeasureData* data2);
		~MeasureComparison();

		void clear(void);
		void compare(MeasureData& data1, MeasureData& data2);
		void compare(MeasureData* data1, MeasureData* data2);

		double getCorrelation7pc(void);

	protected:
		double correlation7pc = 0.0;
};



class MeasureComparisonGrid {
	public:
		             MeasureComparisonGrid     (void);
		             MeasureComparisonGrid     (MeasureDataSet& set1, MeasureDataSet& set2);
		             MeasureComparisonGrid     (MeasureDataSet* set1, MeasureDataSet* set2);
		            ~MeasureComparisonGrid     ();

		void         clear                     (void);
		void         analyze                   (MeasureDataSet& set1, MeasureDataSet& set2);
		void         analyze                   (MeasureDataSet* set1, MeasureDataSet* set2);

		double       getStartTime1             (int index);
		double       getStopTime1              (int index);
		double       getDuration1              (int index);
		int          getMeasure1               (int index);
		std::string  getQon1                   (int index);
		std::string  getQoff1                  (int index);
		double       getScoreDuration1         (void);
		double       getStartTime2             (int index);
		double       getStopTime2              (int index);
		double       getDuration2              (int index);
		int          getMeasure2               (int index);
		std::string  getQon2                   (int index);
		std::string  getQoff2                  (int index);
		double       getScoreDuration2         (void);

		std::ostream&     printCorrelationGrid      (std::ostream& out = std::cout);
		std::ostream&     printCorrelationDiagonal  (std::ostream& out = std::cout);
		std::ostream&     printSvgGrid              (std::ostream& out = std::cout);
		void         getColorMapping           (double input, double& hue, double& saturation,
				 double& lightness);

	private:
		std::vector<std::vector<MeasureComparison>> m_grid;
		MeasureDataSet* m_set1 = NULL;
		MeasureDataSet* m_set2 = NULL;
};



class Tool_simat : public HumTool {
	public:
		         Tool_simat         (void);
		        ~Tool_simat         () {};

		bool     run                (HumdrumFileSet& infiles);
		bool     run                (HumdrumFile& infile1, HumdrumFile& infile2);
		bool     run                (const std::string& indata1, const std::string& indata2, std::ostream& out);
		bool     run                (HumdrumFile& infile1, HumdrumFile& infile2, std::ostream& out);

	protected:
		void     initialize         (HumdrumFile& infile1, HumdrumFile& infile2);
		void     processFile        (HumdrumFile& infile1, HumdrumFile& infile2);

	private:
		MeasureDataSet        m_data1;
		MeasureDataSet        m_data2;
		MeasureComparisonGrid m_grid;

};


class Tool_slurcheck : public HumTool {
	public:
		         Tool_slurcheck    (void);
		        ~Tool_slurcheck    () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void     processFile       (HumdrumFile& infile);
		void     initialize        (void);

	private:

};


class Tool_spinetrace : public HumTool {
	public:
		      Tool_spinetrace          (void);
		     ~Tool_spinetrace          () {};

		bool  run                      (HumdrumFileSet& infiles);
		bool  run                      (HumdrumFile& infile);
		bool  run                      (const std::string& indata, std::ostream& out);
		bool  run                      (HumdrumFile& infile, std::ostream& out);

	protected:
		void  initialize               (HumdrumFile& infile);
		void  processFile              (HumdrumFile& infile);

	private:

};



class Tool_strophe : public HumTool {
	public:
		         Tool_strophe       (void);
		        ~Tool_strophe       () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void     processFile       (HumdrumFile& infile);
		void     initialize        (void);
		void     displayStropheVariants(HumdrumFile& infile);
		void     markWithColor     (HumdrumFile& infile);
		int      markStrophe       (HTp strophestart, HTp stropheend);

	private:
		bool         m_listQ;      // boolean for showing a list of variants
		bool         m_markQ;      // boolean for marking strophes
		std::string  m_marker;     // character for marking strophes
		std::string  m_color;      // color for strphe notes/rests
      std::set<std::string> m_variants;  // used for --list option

};


class Tool_synco : public HumTool {
	public:
		         Tool_synco        (void);
		        ~Tool_synco        () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void      processFile      (HumdrumFile& infile);
		void      initialize       (void);

		void      processStrand    (HTp stok, HTp etok);
		bool      isSyncopated     (HTp token);
		double    getMetricLevel   (HTp token);
		void      markNote         (HTp token);

	private:
		bool        m_hasSyncoQ = false;
		bool        m_infoQ     = false;
		bool        m_fileQ     = false;
		bool        m_allQ      = false;
		int         m_scount    = 0;
		std::string m_color     = "skyblue";

		// for -a option
		int         m_scountTotal    = 0;
		int         m_notecountTotal = 0;
		int         m_fileCount      = 0;

};


class Tool_tabber : public HumTool {
	public:
		      Tool_tabber              (void);
		     ~Tool_tabber              () {};

		bool  run                      (HumdrumFileSet& infiles);
		bool  run                      (HumdrumFile& infile);
		bool  run                      (const std::string& indata, std::ostream& out);
		bool  run                      (HumdrumFile& infile, std::ostream& out);

	protected:
		void  initialize               (HumdrumFile& infile);
		void  processFile              (HumdrumFile& infile);

	private:

};



class Tool_tandeminfo : public HumTool {
	public:
	class Entry {
		public:
			HTp token = NULL;
			std::string description;
			int count = 0;
	};

		         Tool_tandeminfo   (void);
		        ~Tool_tandeminfo   () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);


	protected:
		void     initialize        (void);
		void     processFile       (HumdrumFile& infile);
		void     printEntries      (HumdrumFile& infile);
		void     printEntriesHtml  (HumdrumFile& infile);
		void     printEntriesText  (HumdrumFile& infile);
		void     doCountAnalysis   (void);

		std::string getDescription         (HTp token);
		std::string checkForKeySignature   (const std::string& tok);
		std::string checkForKeyDesignation (const std::string& tok);
		std::string checkForInstrumentInfo (const std::string& tok);
		std::string checkForLabelInfo      (const std::string& tok);
		std::string checkForTimeSignature  (const std::string& tok);
		std::string checkForMeter          (const std::string& tok);
		std::string checkForTempoMarking   (const std::string& tok);
		std::string checkForClef           (const std::string& tok);
		std::string checkForStaffPartGroup (const std::string& tok);
		std::string checkForTuplet         (const std::string& tok);
		std::string checkForHands          (const std::string& tok);
		std::string checkForPosition       (const std::string& tok);
		std::string checkForCue            (const std::string& tok);
		std::string checkForFlip           (const std::string& tok);
		std::string checkForTremolo        (const std::string& tok);
		std::string checkForOttava         (const std::string& tok);
		std::string checkForPedal          (const std::string& tok);
		std::string checkForBracket        (const std::string& tok);
		std::string checkForRscale         (const std::string& tok);
		std::string checkForTimebase       (const std::string& tok);
		std::string checkForTransposition  (const std::string& tok);
		std::string checkForGrp            (const std::string& tok);
		std::string checkForStria          (const std::string& tok);
		std::string checkForFont           (const std::string& tok);
		std::string checkForVerseLabels    (const std::string& tok);
		std::string checkForLanguage       (const std::string& tok);
		std::string checkForStemInfo       (const std::string& tok);
		std::string checkForXywh           (const std::string& tok);
		std::string checkForCustos         (const std::string& tok);
		std::string checkForTextInterps    (const std::string& tok);
		std::string checkForRep            (const std::string& tok);
		std::string checkForPline          (const std::string& tok);
		std::string checkForTacet          (const std::string& tok);
		std::string checkForFb             (const std::string& tok);
		std::string checkForColor          (const std::string& tok);
		std::string checkForThru           (const std::string& tok);

	private:
		bool m_exclusiveQ   = true;   // used with -X option (don't print exclusive interpretation)
		bool m_unknownQ     = false;  // used with -u option (print only unknown tandem interpretations)
		bool m_filenameQ    = false;  // used with -f option (print only unknown tandem interpretations)
		bool m_descriptionQ = false;  // used with -m option (print description of interpretation)
		bool m_locationQ    = false;  // used with -l option (print location of interpretation in file)
		bool m_zeroQ        = false;  // used with -z option (location address by 0-index)
		bool m_tableQ       = false;  // used with -t option (display results as HTML table)
		bool m_closeQ       = false;  // used with --close option (HTML details closed by default)
		bool m_sortQ        = false;  // used with -s (sort entries alphabetically by tandem interpretation)
		bool m_headerOnlyQ  = false;  // used with -h option (process only header interpretations)
		bool m_bodyOnlyQ    = false;  // used with -H option (process only body interpretations)
		bool m_countQ       = false;  // used with -c option (only show unique list with counts);
		bool m_sortByCountQ = false;  // used with -c and -n options (sort from low to high count)
		bool m_sortByReverseCountQ = false;  // used with -c and -N options (sort from high to low count)
		bool m_humdrumQ     = false;  // used with --humdrum option (output data formatted with Humdrum syntax)

		std::string m_unknown = "unknown";

		std::vector<Tool_tandeminfo::Entry> m_entries;
		std::map<std::string, int> m_count;
};


class Tool_tassoize : public HumTool {
	public:
		         Tool_tassoize   (void);
		        ~Tool_tassoize   () {};

		bool     run                (HumdrumFileSet& infiles);
		bool     run                (HumdrumFile& infile);
		bool     run                (const std::string& indata, std::ostream& out);
		bool     run                (HumdrumFile& infile, std::ostream& out);

	protected:
		void     initialize         (HumdrumFile& infile);
		void     processFile        (HumdrumFile& infile);
		void     updateKeySignatures(HumdrumFile& infile, int lineindex);
		void     checkDataLine      (HumdrumFile& infile, int lineindex);
		void     clearStates        (void);
		void     addBibliographicRecords(HumdrumFile& infile);
		void     deleteBreaks       (HumdrumFile& infile);
		void     fixEditorialAccidentals(HumdrumFile& infile);
		void     fixInstrumentAbbreviations(HumdrumFile& infile);
		void     addTerminalLongs   (HumdrumFile& infile);
		void     deleteDummyTranspositions(HumdrumFile& infile);
		std::string   getDate            (void);
		void     adjustSystemDecoration(HumdrumFile& infile);

	private:
		std::vector<std::vector<int>> m_pstates;
		std::vector<std::vector<int>> m_kstates;
		std::vector<std::vector<bool>> m_estates;

};


class Tool_textdur : public HumTool {
	public:
		         Tool_textdur  (void);
		        ~Tool_textdur  () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);


	protected:
		void     initialize        (void);
		void     processFile       (HumdrumFile& infile);
		void     printMelismas     (HumdrumFile& infile);
		void     printDurations     (HumdrumFile& infile);
		void     getTextSpineStarts(HumdrumFile& infile, std::vector<HTp>& starts);
		void     processTextSpine  (std::vector<HTp>& starts, int index);
		int      getMelisma        (HTp tok1, HTp tok2);
		HumNum   getDuration       (HTp tok1, HTp tok2);
		HTp      getTandemKernToken(HTp token);
		void     printInterleaved  (HumdrumFile& infile);
		void     printInterleavedLine(HumdrumLine& line, std::vector<bool>& textTrack);
		void     printTokenAnalysis(HTp token);
		void     printAnalysis      (void);
		void     printDurationAverage(void);
		void     printMelismaAverage(void);
		void     printHtmlContent   (void);
		void     printMelismaHtmlHistogram(void);
		void     printMelismaHtmlHistogram(int index, int maxVal);
		void     printDurationHtmlHistogram(void);
		void     fillInstrumentNameInfo(void);
		std::string getColumnName   (HTp token);

	private:
		std::vector<HTp>                 m_textStarts;
		std::vector<int>                 m_track2column;
		std::vector<std::string>         m_columnName;

		std::vector<std::vector<HTp>>    m_syllables;  // List of syllables in **text/**sylba
		std::vector<std::vector<HumNum>> m_durations;  // List of durations excluding trailing rests
		std::vector<std::vector<int>>    m_melismas;   // List of note counts for syllable

		bool m_analysisQ     = false;  // used with -a option
		bool m_melismaQ      = false;  // used with -m option
		bool m_durationQ     = true;   // used with -m, -d option
		bool m_interleaveQ   = false;  // used with -i option
		HumNum m_RhythmFactor = 1;     // uwed with -1, -2, -8, and later -f #

};


class Tool_thru : public HumTool {
	public:
		         Tool_thru         (void);
		        ~Tool_thru         () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void      processFile         (HumdrumFile& infile);
		void      initialize          (void);

		void      checkOptions        (Options& opts, int argc, char* argv[]);
		void      example             (void);
		void      processData         (HumdrumFile& infile);
		void      usage               (const char* command);
		void      getLabelSequence    (std::vector<std::string>& labelsequence,
		                               const std::string& astring);
		int       getLabelIndex       (std::vector<std::string>& labels, std::string& key);
		void      printLabelList      (HumdrumFile& infile);
		void      printLabelInfo      (HumdrumFile& infile);
		int       getBarline          (HumdrumFile& infile, int line);
		int       adjustFirstBarline  (HumdrumFile& infile);

	private:
		bool      m_listQ = false;    // used with -l option
		bool      m_infoQ = false;    // used with -i option
		bool      m_keepQ = false;    // used with -k option
		bool      m_quietQ = false;   // used with -q option
		std::string    m_variation = "";   // used with -v option
		std::string    m_realization = ""; // used with -r option

};


class Tool_tie : public HumTool {
	public:
		         Tool_tie                (void);
		        ~Tool_tie                () {};

		bool     run                     (HumdrumFileSet& infiles);
		bool     run                     (HumdrumFile& infile);
		bool     run                     (const std::string& indata, std::ostream& out);
		bool     run                     (HumdrumFile& infile, std::ostream& out);

	protected:
		void     processFile             (HumdrumFile& infile);
		void     initialize              (void);
		void     mergeTies               (HumdrumFile& infile);
		void     mergeTie                (HTp token);
		int      markOverfills           (HumdrumFile& infile);
		bool     checkForOverfill        (HTp tok);
		bool     checkForInvisible       (HTp tok);
		void     markNextBarlineInvisible(HTp tok);
		void     splitOverfills          (HumdrumFile& infile);
		void     splitToken              (HTp tok);
		void     carryForwardLeftoverDuration(HumNum duration, HTp tok);
		HumNum   getDurationToNextVisibleBarline(HTp tok);
		HumNum   getDurationToNextBarline(HTp tok);

	private:
		bool          m_printQ         = false;
		bool          m_mergeQ         = false;
		bool          m_splitQ         = false;
		bool          m_markQ          = false;
		bool          m_invisibleQ     = false;
		bool          m_skipInvisibleQ = false;
		std::string   m_mark           = "@";

};


class Tool_timebase : public HumTool {
	public:
		      Tool_timebase       (void);
		     ~Tool_timebase       () {};

		bool  run                 (HumdrumFileSet& infiles);
		bool  run                 (HumdrumFile& infile);
		bool  run                 (const std::string& indata, std::ostream& out);
		bool  run                 (HumdrumFile& infile, std::ostream& out);

	protected:
		void   processFile         (HumdrumFile& infile);
		HumNum getMinimumTime      (HumdrumFile& infile);
		void   expandScore         (HumdrumFile& infile, HumNum mindur);

	private:
		bool   m_grace   = false;
		bool   m_quiet   = false;
		HumNum m_basedur = false;

};



class Tool_transpose : public HumTool {
	public:
		         Tool_transpose  (void);
		        ~Tool_transpose  () {};

		bool     run             (HumdrumFileSet& infiles);
		bool     run             (HumdrumFile& infile);
		bool     run             (const std::string& indata, std::ostream& out);
		bool     run             (HumdrumFile& infile, std::ostream& out);

	protected:

		// auto transpose functions:
		void     initialize             (HumdrumFile& infile);
		void     convertScore           (HumdrumFile& infile, int style);
		void     processFile            (HumdrumFile& infile,
		                                 std::vector<bool>& spineprocess);
		void     convertToConcertPitches(HumdrumFile& infile, int line,
		                                 std::vector<int>& tvals);
		void     convertToWrittenPitches(HumdrumFile& infile, int line,
		                                 std::vector<int>& tvals);
		void     printNewKeySignature   (const std::string& keysig, int trans);
		void     processInterpretationLine(HumdrumFile& infile, int line,
		                                 std::vector<int>& tvals, int style);
		int      isKeyMarker            (const std::string& str);
		void     printNewKeyInterpretation(HumdrumLine& aRecord,
		                                 int index, int transval);
		int      hasTrMarkers           (HumdrumFile& infile, int line);
		void     printHumdrumKernToken  (HumdrumLine& record, int index,
		                                 int transval);
		void     printHumdrumMxhmToken(HumdrumLine& record, int index,
		                                 int transval);
		int      checkForDeletedLine    (HumdrumFile& infile, int line);
		int      getBase40ValueFromInterval(const std::string& string);
		void     example                (void);
		void     usage                  (const std::string& command);
		void     printHumdrumDataRecord (HumdrumLine& record,
		                                 std::vector<bool>& spineprocess);

		double   pearsonCorrelation     (int size, double* x, double* y);
		void     doAutoTransposeAnalysis(HumdrumFile& infile);
		void     addToHistogramDouble   (std::vector<std::vector<double> >& histogram,
		                                 int pc, double start, double dur,
		                                 double tdur, int segments);
		double   storeHistogramForTrack (std::vector<std::vector<double> >& histogram,
		                                 HumdrumFile& infile, int track,
		                                 int segments);
		void     printHistograms        (int segments, std::vector<int> ktracks,
		                                std::vector<std::vector<std::vector<double> > >&
		                                 trackhist);
		void     doAutoKeyAnalysis      (std::vector<std::vector<std::vector<double> > >&
		                                 analysis, int level, int hop, int count,
		                                 int segments, std::vector<int>& ktracks,
		                                 std::vector<std::vector<std::vector<double> > >&
		                                 trackhist);
		void     doTrackKeyAnalysis     (std::vector<std::vector<double> >& analysis,
		                                 int level, int hop, int count,
		                                 std::vector<std::vector<double> >& trackhist,
		                                 std::vector<double>& majorweights,
		                                 std::vector<double>& minorweights);
		void     identifyKeyDouble      (std::vector<double>& correls,
		                                 std::vector<double>& histogram,
		                                 std::vector<double>& majorweights,
		                                 std::vector<double>& minorweights);
		void     fillWeightsWithKostkaPayne(std::vector<double>& maj,
		                                 std::vector<double>& min);
		void     printRawTrackAnalysis  (std::vector<std::vector<std::vector<double> > >&
		                                 analysis, std::vector<int>& ktracks);
		void     doSingleAnalysis       (std::vector<double>& analysis,
		                                 int startindex, int length,
		                                 std::vector<std::vector<double> >& trackhist,
		                                 std::vector<double>& majorweights,
		                                 std::vector<double>& minorweights);
		void     identifyKey            (std::vector<double>& correls,
		                                 std::vector<double>& histogram,
		                                 std::vector<double>& majorweights,
		                                 std::vector<double>& minorweights);
		void     doTranspositionAnalysis(std::vector<std::vector<std::vector<double> > >&
		                                 analysis);
		int      calculateTranspositionFromKey(int targetkey,
		                                 HumdrumFile& infile);
		void     printTransposedToken   (HumdrumFile& infile, int row, int col,
		                                 int transval);
		void     printTransposeInformation(HumdrumFile& infile,
		                                 std::vector<bool>& spineprocess,
		                                 int line, int transval);
		int      getTransposeInfo       (HumdrumFile& infile, int row, int col);
		void     printNewKernString     (const std::string& string, int transval);

	private:
		int      transval     = 0;   // used with -b option
		int      ssettonicQ   = 0;   // used with -k option
		int      ssettonic    = 0;   // used with -k option
		int      currentkey   = 0;
		int      autoQ        = 0;   // used with --auto option
		int      debugQ       = 0;   // used with --debug option
		std::string   spinestring  = "";  // used with -s option
		int      octave       = 0;   // used with -o option
		int      concertQ     = 0;   // used with -C option
		int      writtenQ     = 0;   // used with -W option
		int      quietQ       = 0;   // used with -q option
		int      instrumentQ  = 0;   // used with -I option
};



class Tool_tremolo : public HumTool {
	public:
		         Tool_tremolo       (void);
		        ~Tool_tremolo       () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void    processFile        (HumdrumFile& infile);
		void    removeMarkup       (void);
		void    expandTremolos     (void);
		void    expandFingerTremolo(HTp token);
		void    expandTremolo      (HTp token);
		void    addTremoloInterpretations(HumdrumFile& infile);
		void    storeFirstTremoloNoteInfo(HTp token);
		void    storeLastTremoloNoteInfo(HTp token);
		HTp     getNextNote        (HTp token);

	private:
		bool    m_keepQ      = false;
		bool    m_modifiedQ  = false;
		std::vector<HTp> m_markup_tokens;
		std::vector<HumNum> m_first_tremolo_time;
		std::vector<HumNum> m_last_tremolo_time;

};


class Tool_trillspell : public HumTool {
	public:
		      Tool_trillspell     (void);
		     ~Tool_trillspell     () {};

		bool  run                 (HumdrumFileSet& infiles);
		bool  run                 (HumdrumFile& infile);
		bool  run                 (const std::string& indata, std::ostream& out);
		bool  run                 (HumdrumFile& infile, std::ostream& out);

	protected:
		void  processFile         (HumdrumFile& infile);
		bool  analyzeOrnamentAccidentals(HumdrumFile& infile);
		void  resetDiatonicStatesWithKeySignature(std::vector<int>& states,
		                                          std::vector<int>& signature);
		void  fillKeySignature    (std::vector<int>& states, const std::string& keysig);
		int   getBase40           (int diatonic, int accidental);

	private:
		bool m_xmark = false;

};



class Tool_tspos : public HumTool {
	public:
		         Tool_tspos  (void);
		        ~Tool_tspos  () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void             initialize        (HumdrumFile& infile);
		void             processFile       (HumdrumFile& infile);
		std::vector<int> getMidiNotes(std::vector<HTp>& kernNotes);
		std::vector<int> getChordPositions(std::vector<int>& midiNotes);
		std::vector<int> getNoteMods(std::vector<int>& midiNotes);
		std::vector<int> getThirds(std::vector<int>& midiNotes);
		std::vector<int> getFifths(std::vector<int>& midiNotes);
		void             labelChordPositions(std::vector<HTp>& kernNotes, std::vector<int>& chordPositions);
		void             labelThirds(std::vector<HTp>& kernNotes, std::vector<int>& thirdPositions);
		void             labelFifths(std::vector<HTp>& kernNotes, std::vector<int>& fifthPositions);
		void             keepOnlyDoubles(std::vector<int>& output);
		void             checkForTriadicSonority(std::vector<int>& positions, int line);
		std::string      generateStatistics(HumdrumFile& infile);
		std::vector<std::string> getTrackNames(HumdrumFile& infile);
		int              getVectorSum(std::vector<int>& input);
		void             analyzeVoiceCount(HumdrumFile& infile);
		int              countVoicesOnLine(HumdrumFile& infile, int line);
		std::string      generateTable(HumdrumFile& infile, std::vector<std::string>& name);
		bool             hasFullTriadAttack(HumdrumLine& line);
		void             avoidRdfCollisions(HumdrumFile& infile);
		void             printUsedMarkers(void);
		std::string      makeOpacityColor(std::string& color, double value, double total, bool enhance = false);
		int              getToolCounter(HumdrumFile& infile);
		std::string      makePercentString(double value, double total, int digits);
		int              logisticColorMap(double input, double max);

	private:
		std::string m_root_marker      = "@";
		std::string m_third_marker     = "N";
		std::string m_fifth_marker     = "Z";
		std::string m_3rd_root_marker  = "j";
		std::string m_3rd_third_marker = "l";
		std::string m_5th_root_marker  = "V";
		std::string m_5th_fifth_marker = "|";

		std::vector<int> m_used_markers;

		std::string m_root_color       = "#DC143C"; // crimson
		std::string m_third_color      = "#32CD32"; // limegreen
		std::string m_fifth_color      = "#4169E1"; // royalblue
		std::string m_3rd_root_color   = "#8B0000"; // darkred
		std::string m_3rd_third_color  = "#008000"; // green
		std::string m_5th_root_color   = "#8B0000"; // darkred
		std::string m_5th_fifth_color  = "#4682B4"; // steelblue

		bool m_colorThirds = true;   // used with -3 option (to negate)
		bool m_colorFifths = true;   // used with -5 option (to negate)
		bool m_colorTriads = true;   // used with -T option (to negate)
		bool m_doubleQ     = false;  // used with -d option

		bool m_topQ = false;         // used with --top option
		bool m_tableQ = false;       // used with -t option
		bool m_triadAttack = false;  // used with -x option

		// Statistical data variables:
		std::vector<bool> m_triadState;

		// m_partTriadPositions -- count the number of chordal positions by
		// voice.  The first dimention is the track number of the part, and
		// the second dimension is the counts for 7 categories:
		// 0 = count of root positions in full triadic chords
		// 1 = count of third positions in full triadic chords
		// 2 = count of fifth positions in full triadic chords
		// 3 = count of root positions in partial triadic chords ("open thirds")
		// 4 = count of third positions in partial triadic chords
		// 5 = count of root positions in partial triadic chords ("open fifths")
		// 6 = count of fifth positions in partial triadic chords
		std::vector<std::vector<int>> m_partTriadPositions;
		int m_positionCount = 7; // entries in 2nd dim. of m_partTriadPositions

		std::string m_toolName = "tspos";

		std::vector<int> m_voiceCount;
		// m_voice: used with -v option to limit analysis to sonorities that
		// have the given voice count. 0 means analyze any voice counts.
		int m_voice = 0;

		bool m_compressedQ = false;

		bool m_minorQ = true;
		bool m_majorQ = true;

		bool m_questionQ = true;
		int  m_toolCount = 0;

		std::vector<std::string> m_fullNames;
};


class Tool_vcross : public HumTool {
	public:
		         Tool_vcross     (void);
		        ~Tool_vcross     () {};

		bool     run               (HumdrumFileSet& infiles);
		bool     run               (HumdrumFile& infile);
		bool     run               (const std::string& indata, std::ostream& out);
		bool     run               (HumdrumFile& infile, std::ostream& out);

	protected:
		void    processFile        (HumdrumFile& infile);
		void    initialize         (void);
		void    getMidiInfo        (std::vector<int>& midis, HTp token);
		void    compareVoices      (std::vector<HTp>& higher, std::vector<HTp>& lower);
		void    processLine        (HumdrumFile& infile, int index);

	private:
		bool m_redQ = false;
		bool m_greenQ = false;
		bool m_blueQ = false;


};


} // end of namespace hum


#endif /* _HUMLIB_H_INCLUDED */



