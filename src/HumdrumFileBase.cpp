//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sat Aug  8 12:24:49 PDT 2015
// Last Modified: Fri Aug 14 21:57:09 PDT 2015
// Filename:      HumdrumFileBase.h
// URL:           https://github.com/craigsapp/minHumdrum/blob/master/src/HumdrumFileBase.h
// Syntax:        C++11
// vim:           ts=3 noexpandtab
//
// Description:   Used to store Humdrum text lines from input stream
//                for further parsing.  This class analyzes the basic
//                spine structure after reading a Humdrum file.  The
//                HumdrumFileStructure class continues structural analysis,
//                primarily of rhythm (generated by **kern, **recip and
//                **koto data).
//

#include "HumdrumFileBase.h"

#include <sstream>
#include <fstream>

namespace minHumdrum {

// START_MERGE


//////////////////////////////
//
// HumdrumFileBase::HumdrumFileBase --
//

HumdrumFileBase::HumdrumFileBase(void) {
	addToTrackStarts(NULL);
}



//////////////////////////////
//
// HumdrumFileBase::~HumdrumFileBase --
//

HumdrumFileBase::~HumdrumFileBase() { }



//////////////////////////////
//
// HumdrumFileBase::operator[] -- Negative values will be in reference to the
//    end of the list of lines.
//

HumdrumLine& HumdrumFileBase::operator[](int index) {
	if (index < 0) {
		index = lines.size() - index;
	}
	if ((index < 0) || (index >= lines.size())) {
		cerr << "Error: invalid index: " << index << endl;
		index = lines.size()-1;
	}
	return *lines[index];
}



//////////////////////////////
//
// HumdrumFileBase::read -- Load file contents from input stream without
//    parsing the rhythmic information in the file.
//

bool HumdrumFileBase::read(const string& filename) {
	return HumdrumFileBase::read(filename.c_str());
}


bool HumdrumFileBase::read(const char* filename) {
	ifstream infile;
	if ((strlen(filename) == 0) || (strcmp(filename, "-") == 0)) {
		return HumdrumFileBase::read(cin);
	} else {
		infile.open(filename);
		if (!infile.is_open()) {
			return false;
		}
	}
	int status = HumdrumFileBase::read(infile);
	infile.close();
	return status;
}


bool HumdrumFileBase::read(istream& infile) {
	char buffer[123123] = {0};
	HumdrumLine* s;
	while (infile.getline(buffer, sizeof(buffer), '\n')) {
		s = new HumdrumLine(buffer);
		s->setOwner(this);
		lines.push_back(s);
	}
	if (!analyzeTokens()         ) { return false; }
	if (!analyzeLines()          ) { return false; }
	if (!analyzeSpines()         ) { return false; }
	if (!analyzeLinks()          ) { return false; }
	if (!analyzeTracks()         ) { return false; }
	return true;
}



//////////////////////////////
//
// HumdrumFileBase::ReadString -- Read contents from a string rather than
//    an istream or filename.
//

bool HumdrumFileBase::readString(const string& contents) {
	stringstream infile;
	infile << contents;
	return read(infile);
}


bool HumdrumFileBase::readString(const char* contents) {
	stringstream infile;
	infile << contents;
	return read(infile);
}



//////////////////////////////
//
// HumdrumFileBase::analyzeTokens -- Generate token array from
//    current state of lines.  If either state is changed, then the
//    other state becomes invalid.  See createLinesFromTokens for
//		regeneration of lines from tokens.
//

bool HumdrumFileBase::analyzeTokens(void) {
	int i;
	for (i=0; i<lines.size(); i++) {
		lines[i]->createTokensFromLine();
	}
	return true;
}



//////////////////////////////
//
// HumdrumFileBase::createLinesFromTokens -- Generate Humdrum lines from
//   the list of tokens.
//

void HumdrumFileBase::createLinesFromTokens(void) {
	for (int i=0; i<lines.size(); i++) {
		lines[i]->createLineFromTokens();
	}
}



////////////////////////////
//
// HumdrumFileBase::append -- Add a line to the file's contents.
//

void HumdrumFileBase::append(const char* line) {
	HumdrumLine* s = new HumdrumLine(line);
	lines.push_back(s);
}


void HumdrumFileBase::append(const string& line) {
	HumdrumLine* s = new HumdrumLine(line);
	lines.push_back(s);
}



////////////////////////////
//
// HumdrumFileBase::getLineCount -- Return the number of lines.
//

int HumdrumFileBase::getLineCount(void) const {
	return lines.size();
}



//////////////////////////////
//
// HumdrumFileBase::getMaxTrack -- returns the number of primary spines in the data.
//

int HumdrumFileBase::getMaxTrack(void) const {
	return trackstarts.size() - 1;
}



//////////////////////////////
//
// HumdrumFileBase::printSpineInfo --
//

ostream& HumdrumFileBase::printSpineInfo(ostream& out) {
	for (int i=0; i<getLineCount(); i++) {
		lines[i]->printSpineInfo(out) << '\n';
	}
	return out;
}



//////////////////////////////
//
// HumdrumFileBase::printDataTypeInfo --
//

ostream& HumdrumFileBase::printDataTypeInfo(ostream& out) {
	for (int i=0; i<getLineCount(); i++) {
		lines[i]->printDataTypeInfo(out) << '\n';
	}
	return out;
}



//////////////////////////////
//
// HumdrumFileBase::printTrackInfo --
//

ostream& HumdrumFileBase::printTrackInfo(ostream& out) {
	for (int i=0; i<getLineCount(); i++) {
		lines[i]->printTrackInfo(out) << '\n';
	}
	return out;
}



//////////////////////////////
//
// HumdrumFileBase::getTrackStart --
//

HumdrumToken* HumdrumFileBase::getTrackStart(int track) const {
	if ((track > 0) && (track < trackstarts.size())) {
		return trackstarts[track];
	} else {
		return NULL;
	}
}



//////////////////////////////
//
// HumdrumFileBase::getTrackEndCount -- return the number of ending tokens
//    for the given track
//

int HumdrumFileBase::getTrackEndCount(int track) const {
	if (track < 0) {
		track += trackends.size();
	}
	if (track < 0) {
		return 0;
	}
	if (track >= trackends.size()) {
		return 0;
	}
	return trackends[track].size();
}



//////////////////////////////
//
// HumdrumFileBase::getTrackEnd -- return the number of ending tokens
//    for the given track
//

HumdrumToken* HumdrumFileBase::getTrackEnd(int track, int subtrack) const {
	if (track < 0) {
		track += trackends.size();
	}
	if (track < 0) {
		return NULL;
	}
	if (track >= trackends.size()) {
		return NULL;
	}
	if (subtrack < 0) {
		subtrack += trackends[track].size();
	}
	if (subtrack < 0) {
		return NULL;
	}
	if (subtrack >= trackends[track].size()) {
		return NULL;
	}
	return trackends[track][subtrack];
}



//////////////////////////////
//
// HumdrumFileBase::analyzeLines -- Mark the line's index number in the
//    HumdrumFileBase.
//

bool HumdrumFileBase::analyzeLines(void) {
	for (int i=0; i<lines.size(); i++) {
		lines[i]->setLineIndex(i);
	}
	return true;
}



//////////////////////////////
//
// HumdrumFileBase::analyzeTracks -- Analyze the track structure of the
//     data.  Returns false if there was a parse error.
//

bool HumdrumFileBase::analyzeTracks(void) {
	for (int i=0; i<lines.size(); i++) {
		int status = lines[i]->analyzeTracks();
		if (!status) {
			return false;
		}
	}
	return true;
}



//////////////////////////////
//
// HumdrumFileBase::analyzeLinks -- Generate forward and backwards spine links
//    for each token.
//

bool HumdrumFileBase::analyzeLinks(void) {
	HumdrumLine* next     = NULL;
	HumdrumLine* previous = NULL;

	for (int i=0; i<lines.size(); i++) {
		if (!lines[i]->hasSpines()) {
			continue;
		}
		previous = next;
		next = lines[i];
		if (previous != NULL) {
			if (!stitchLinesTogether(*previous, *next)) {
				return false;
			}
		}
	}
	return true;
}



//////////////////////////////
//
// HumdrumFileBase::stitchLinesTogether -- Make forward/backward links for
//    tokens on each line.
//

bool HumdrumFileBase::stitchLinesTogether(HumdrumLine& previous,
		HumdrumLine& next) {
	int i;


	// first handle simple cases where the spine assignments are one-to-one:
	if (!previous.isInterpretation() && !next.isInterpretation()) {
		if (previous.getTokenCount() != next.getTokenCount()) {
			cerr << "Error lines " << (previous.getLineNumber())
			     << " and " << (next.getLineNumber()) << " not same length\n";
			cerr << "Line " << (previous.getLineNumber()) << ": "
			     << previous << endl;
			cerr << "Line " << (next.getLineNumber()) << ": "
			     << next << endl;
			return false;
		}
		for (i=0; i<previous.getTokenCount(); i++) {
			previous.token(i).makeForwardLink(next.token(i));
		}
		return true;
	}
	int ii = 0;
	for (i=0; i<previous.getTokenCount(); i++) {
		if (!previous.token(i).isManipulator()) {
			previous.token(i).makeForwardLink(next.token(ii++));
		} else if (previous.token(i).isSplitInterpretation()) {
			// connect the previous token to the next two tokens.
			previous.token(i).makeForwardLink(next.token(ii++));
			previous.token(i).makeForwardLink(next.token(ii++));
		} else if (previous.token(i).isMergeInterpretation()) {
			// connect multiple previous tokens which are adjacent *v
			// spine manipulators to the current next token.
			while ((i<previous.getTokenCount()) &&
					previous.token(i).isMergeInterpretation()) {
				previous.token(i).makeForwardLink(next.token(ii));
				i++;
			}
			i--;
			ii++;
		} else if (previous.token(i).isExchangeInterpretation()) {
			// swapping the order of two spines.
			if ((i<previous.getTokenCount()) &&
					previous.token(i+1).isExchangeInterpretation()) {
				previous.token(i+1).makeForwardLink(next.token(ii++));
				previous.token(i).makeForwardLink(next.token(ii++));
			}
			i++;
		} else if (previous.token(i).isTerminateInterpretation()) {
			// No link should be made.  There may be a problem if a
			// new segment is given (this should be handled by a
			// HumdrumSet class, not HumdrumFileBase.
		} else if (previous.token(i).isAddInterpretation()) {
			// A new data stream is being added, the next linked token
			// should be an exclusive interpretation.
			if (!next.token(ii+1).isExclusiveInterpretation()) {
				cerr << "Error: expecting exclusive interpretation on line "
				     << next.getLineNumber() << " at token " << i << " but got "
				     << next.token(i) << endl;
				return false;
			}
			previous.token(i).makeForwardLink(next.token(ii++));
			ii++;
		} else if (previous.token(i).isExclusiveInterpretation()) {
			previous.token(i).makeForwardLink(next.token(ii++));
		} else {
			cerr << "Error: should not get here" << endl;
			return false;
		}
	}

	if ((i != previous.getTokenCount()) || (ii != next.getTokenCount())) {
		cerr << "Error: cannot stitch lines together due to alignment problem\n";
		cerr << "Line " << previous.getLineNumber() << ": "
		     << previous << endl;
		cerr << "Line " << next.getLineNumber() << ": "
		     << next << endl;
		cerr << "I = " <<i<< " token count " << previous.getTokenCount() << endl;
		cerr << "II = " <<ii<< " token count " << next.getTokenCount() << endl;
	}

	return true;
}



//////////////////////////////
//
// HumdrumFileBase::analyzeSpines -- Analyze the spine structure of the
//     data.  Returns false if there was a parse error.
//

bool HumdrumFileBase::analyzeSpines(void) {
	vector<string> datatype;
	vector<string> sinfo;
	vector<vector<HumdrumToken*> > lastspine;
	trackstarts.resize(0);
	trackends.resize(0);
	addToTrackStarts(NULL);

	bool init = false;
	int i, j;
	for (i=0; i<getLineCount(); i++) {
		if (!lines[i]->hasSpines()) {
			lines[i]->token(0).setFieldIndex(0);
			continue;
		}
		if ((init == false) && !lines[i]->isExclusive()) {
			cerr << "Error on line: " << (i+1) << ':' << endl;
			cerr << "   Data found before exclusive interpretation" << endl;
			cerr << "   LINE: " << *lines[i] << endl;
			return false;
		}
		if ((init == false) && lines[i]->isExclusive()) {
			// first line of data in file.
			init = true;
			datatype.resize(lines[i]->getTokenCount());
			sinfo.resize(lines[i]->getTokenCount());
			lastspine.resize(lines[i]->getTokenCount());
			for (j=0; j<lines[i]->getTokenCount(); j++) {
				datatype[j] = lines[i]->getTokenString(j);
				addToTrackStarts(&lines[i]->token(j));
				sinfo[j]    = to_string(j+1);
				lines[i]->token(j).setSpineInfo(sinfo[j]);
				lines[i]->token(j).setFieldIndex(j);
				lastspine[j].push_back(&(lines[i]->token(j)));
			}
			continue;
		}
		if (datatype.size() != lines[i]->getTokenCount()) {
			cerr << "Error on line " << (i+1) << ':' << endl;
			cerr << "   Expected " << datatype.size() << " fields,"
			     << " but found " << lines[i]->getTokenCount() << endl;
			return false;
		}
		for (j=0; j<lines[i]->getTokenCount(); j++) {
			lines[i]->token(j).setSpineInfo(sinfo[j]);
			lines[i]->token(j).setFieldIndex(j);
		}
		if (!lines[i]->isManipulator()) {
			continue;
		}
		if (!adjustSpines(*lines[i], datatype, sinfo)) { return false; }
	}
	return true;
}



//////////////////////////////
//
// HumdrumFileBase::addToTrackStarts --
//

void HumdrumFileBase::addToTrackStarts(HumdrumToken* token) {
	if (token == NULL) {
		trackstarts.push_back(NULL);
		trackends.resize(trackends.size()+1);
	} else if ((trackstarts.size() > 1) && (trackstarts.back() == NULL)) {
		trackstarts.back() = token;
	} else {
		trackstarts.push_back(token);
		trackends.resize(trackends.size()+1);
	}
}



//////////////////////////////
//
// HumdrumFileBase::adjustSpines -- adjust datatype and spineinfo based
//   on manipulators.
//

bool HumdrumFileBase::adjustSpines(HumdrumLine& line, vector<string>& datatype,
		vector<string>& sinfo) {
	vector<string> newtype;
	vector<string> newinfo;
	int mergecount = 0;
	int i, j;
	for (i=0; i<line.getTokenCount(); i++) {
		if (line.token(i).isSplitInterpretation()) {
			newtype.resize(newtype.size() + 1);
			newtype.back() = datatype[i];
			newtype.resize(newtype.size() + 1);
			newtype.back() = datatype[i];
			newinfo.resize(newinfo.size() + 2);
			newinfo[newinfo.size()-2] = '(' + sinfo[i] + ")a";
			newinfo[newinfo.size()-1] = '(' + sinfo[i] + ")b";
		} else if (line.token(i).isMergeInterpretation()) {
			mergecount = 0;
			for (j=i+1; j<line.getTokenCount(); j++) {
				if (line.token(j).isMergeInterpretation()) {
					mergecount++;
				} else {
					break;
				}
			}
			newinfo.resize(newtype.size() + 1);
			newinfo.back() = getMergedSpineInfo(sinfo, i, mergecount);
			newtype.resize(newtype.size() + 1);
			newtype.back() = datatype[i];
			i += mergecount;
		} else if (line.token(i).isAddInterpretation()) {
			newtype.resize(newtype.size() + 1);
			newtype.back() = datatype[i];
			newtype.resize(newtype.size() + 1);
			newtype.back() = "";
			newinfo.resize(newinfo.size() + 1);
			newinfo.back() = sinfo[i];
			newinfo.resize(newinfo.size() + 1);
			addToTrackStarts(NULL);
			newinfo.back() = to_string(getMaxTrack());
		} else if (line.token(i).isExchangeInterpretation()) {
			if (i < line.getTokenCount() - 1) {
				if (line.token(i).isExchangeInterpretation()) {
					// exchange spine information
					newtype.resize(newtype.size() + 1);
					newtype.back() = datatype[i+1];
					newtype.resize(newtype.size() + 1);
					newtype.back() = datatype[i];
					newinfo.resize(newinfo.size() + 1);
					newinfo.back() = sinfo[i+1];
					newinfo.resize(newinfo.size() + 1);
					newinfo.back() = sinfo[i];
				} else {
					cerr << "ERROR1 in *x calculation" << endl;
					return false;
				}
				i++;
			} else {
				cerr << "ERROR2 in *x calculation" << endl;
				cerr << "Index " << i << " larger than allowed: "
				     << line.getTokenCount() - 1 << endl;
				return false;
			}
		} else if (line.token(i).isTerminateInterpretation()) {
			// store pointer to terminate token in trackends
			trackends[trackstarts.size()-1].push_back(&(line.token(i)));
		} else if (((string)line.token(i)).substr(0, 2) == "**") {
			newtype.resize(newtype.size() + 1);
			newtype.back() = line.getTokenString(i);
			newinfo.resize(newinfo.size() + 1);
			newinfo.back() = sinfo[i];
			if (!((trackstarts.size() > 1) && (trackstarts.back() == NULL))) {
				cerr << "Error: Exclusive interpretation with no preparation "
				     << "on line " << line.getLineIndex()
				     << " spine index " << i << endl;
				cerr << "Line: " << line << endl;
				return false;
			}
			if (trackstarts.back() == NULL) {
cout << "GOING TO ADD " << line.token(i) << endl;
				addToTrackStarts(&line.token(i));
			}
		} else {
			// should only be null interpretation, but doesn't matter
			newtype.resize(newtype.size() + 1);
			newtype.back() = datatype[i];
			newinfo.resize(newinfo.size() + 1);
			newinfo.back() = sinfo[i];
		}
	}

	datatype.resize(newtype.size());
	sinfo.resize(newinfo.size());
	for (i=0; i<newtype.size(); i++) {
		datatype[i] = newtype[i];
		sinfo[i]    = newinfo[i];
	}

	return true;
}



//////////////////////////////
//
// HumdrumFileBase::getMergedSpineInfo -- Will only simplify a two-spine
//   merge.  Should be expanded to larger spine mergers.
//

string HumdrumFileBase::getMergedSpineInfo(vector<string>& info, int starti,
		int extra) {
	string output;
	int len1;
	int len2;
	if (extra == 1) {
		len1 = info[starti].size();
		len2 = info[starti+1].size();
		if (len1 == len2) {
			if (info[starti].substr(0, len1-1) ==
					info[starti+1].substr(0,len2-1)) {
				output = info[starti].substr(1, len1-3);
				return output;
			}
		}
		output = info[starti] + " " + info[starti+1];
		return output;
	}
	output = info[starti];
	for (int i=0; i<extra; i++) {
		output += " " + info[starti+1+extra];
	}
	return output;
}



//////////////////////////////
//
// HumdrumFileBase::analyzeNonNullDataTokens -- For null data tokens, indicate
//    the previous non-null token which the null token refers to.  After
//    a spine merger, there may be multiple previous tokens, so you would
//		have to decide on the actual source token on based on subtrack or
//    subspine information.  The function also gives links to the previous/next
//    non-null tokens, skipping over intervening null data tokens.
//

bool HumdrumFileBase::analyzeNonNullDataTokens(void) {
	vector<HumdrumToken*> ptokens;

	// analyze forward tokens:
	for (int i=1; i<=getMaxTrack(); i++) {
		if (!processNonNullDataTokensForTrackForward(getTrackStart(i),
				ptokens)) {
			return false;
		}
	}

	// analyze backward tokens:
	for (int i=1; i<=getMaxTrack(); i++) {
		for (int j=0; j<getTrackEndCount(i); j++) {
			if (!processNonNullDataTokensForTrackBackward(getTrackEnd(i, j),
					ptokens)) {
				return false;
			}
		}
	}
	return true;
}



//////////////////////////////
//
// HumdurmFile::processNonNullDataTokensForTrackBackward --
//

bool HumdrumFileBase::processNonNullDataTokensForTrackBackward(
		HumdrumToken* endtoken, vector<HumdrumToken*> ptokens) {

	HumdrumToken* token = endtoken;
	int tcount = token->getPreviousTokenCount();
	while (tcount > 0) {
		for (int i=1; i<tcount; i++) {
			if (!processNonNullDataTokensForTrackBackward(
					token->getPreviousToken(i), ptokens)) {
				return false;
			}
		}
		if (token->isData()) {
			addUniqueTokens(token->nextNonNullTokens, ptokens);
			if (!token->isNull()) {
				ptokens.resize(0);
				ptokens.push_back(token);
			}
		}
		// Data tokens can only be followed by up to one previous token,
		// so no need to check for more than one next token.
		token = token->getPreviousToken(0);
		tcount = token->getPreviousTokenCount();
	}

	return true;
}



//////////////////////////////
//
// HumdurmFile::processNonNullDataTokensForTrackForward --
//

bool HumdrumFileBase::processNonNullDataTokensForTrackForward(
		HumdrumToken* starttoken, vector<HumdrumToken*> ptokens) {
	HumdrumToken* token = starttoken;
	int tcount = token->getNextTokenCount();
	while (tcount > 0) {
		if (!token->isData()) {
			for (int i=1; i<tcount; i++) {
				if (!processNonNullDataTokensForTrackForward(
						token->getNextToken(i), ptokens)) {
					return false;
				}
			}
		} else {
			addUniqueTokens(token->previousNonNullTokens, ptokens);
			if (!token->isNull()) {
				ptokens.resize(0);
				ptokens.push_back(token);
			}
		}
		// Data tokens can only be followed by up to one next token,
		// so no need to check for more than one next token.
		token = token->getNextToken(0);
		tcount = token->getNextTokenCount();
	}

	return true;
}



//////////////////////////////
//
// HumdrumFileBase::addUniqueTokens --
//

void HumdrumFileBase::addUniqueTokens(vector<HumdrumToken*>& target,
		vector<HumdrumToken*>& source) {
	int i, j;
	bool found;
	for (i=0; i<source.size(); i++) {
		found = false;
		for (j=0; j<target.size(); j++) {
			if (source[i] == target[i]) {
				found = true;
			}
		}
		if (!found) {
			target.push_back(source[i]);
		}
	}
}



//////////////////////////////
//
// operator<< -- Print a HumdrumFileBase.
//

ostream& operator<<(ostream& out, HumdrumFileBase& infile) {
	for (int i=0; i<infile.getLineCount(); i++) {
		out << infile[i] << '\n';
	}
	return out;
}

// END_MERGE

} // end namespace std;



