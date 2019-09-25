//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Thu Jun  3 14:08:25 PDT 2010
// Last Modified: Tue Jun 15 14:15:42 PDT 2010 (added tied note functionality)
// Filename:      ...sig/src/sigInfo/MuseData.cpp
// Web Address:   http://sig.sapp.org/src/sigInfo/MuseData.cpp
// Syntax:        C++
// vim:           ts=3
//
// Description:   A class that multiple MuseRecord lines.
//

#include "MuseData.h"
#include "HumRegex.h"

#include <string.h>
#include <cctype>
#include <stdlib.h>

#include <sstream>
#include <fstream>

using namespace std;

namespace hum {

// START_MERGE


///////////////////////////////////////////////////////////////////////////
//
// MuseEventSet class functions --
//


//////////////////////////////
//
// MuseEventSet::MuseEventSet --
//

MuseEventSet::MuseEventSet (void) {
	events.reserve(20);
	clear();
}


MuseEventSet::MuseEventSet(HumNum atime) {
	setTime(atime);
	events.reserve(20);
}



//////////////////////////////
//
// MuseData::operator= --
//

MuseData& MuseData::operator=(MuseData& input) {
	if (this == &input) {
		return *this;
	}
	data.resize(input.data.size());
	MuseRecord* temprec;
	int i;
	for (i=0; i<(int)data.size(); i++) {
		temprec = new MuseRecord;
		*temprec = *(input.data[i]);
		data[i] = temprec;
	}
	// do something with sequence...
	name = input.name;
	return *this;
}



//////////////////////////////
//
// MuseEventSet::clear --
//

void MuseEventSet::clear(void) {
	events.clear();
	absbeat.setValue(0,1);
}



//////////////////////////////
//
// MuseEventSet::setTime --
//

void MuseEventSet::setTime(HumNum abstime) {
	absbeat = abstime;
}



//////////////////////////////
//
// MuseEventSet::getTime --
//

HumNum MuseEventSet::getTime(void) {
	return absbeat;
}



//////////////////////////////
//
// MuseEventSet::appendRecord -- still have to sort after insertion...
//   also add a removeEvent function so deleted elements can be removed
//   gracefully.
//

void MuseEventSet::appendRecord(MuseRecord* arecord) {
	events.push_back(arecord);
}



//////////////////////////////
//
// MuseEventSet::operator[] --
//

MuseRecord& MuseEventSet::operator[](int eindex) {
	return *(events[eindex]);
}



//////////////////////////////
//
// MuseEventSet::operator= --
//

MuseEventSet MuseEventSet::operator=(MuseEventSet& anevent) {
	if (&anevent == this) {
		return *this;
	}

	this->absbeat = anevent.absbeat;
	this->events.resize(anevent.events.size());
	int i;
	for (i=0; i<(int)this->events.size(); i++) {
		this->events[i] = anevent.events[i];
	}
	return *this;
}



//////////////////////////////
//
// MuseEventSet::getEventCount --
//

int MuseEventSet::getEventCount(void) {
	return (int)events.size();
}



///////////////////////////////////////////////////////////////////////////
//
// MuseData class functions --
//


//////////////////////////////
//
// MuseData::MuseData --
//

MuseData::MuseData(void) {
	data.reserve(100000);
}

MuseData::MuseData(MuseData& input) {
	data.resize(input.data.size());
	MuseRecord* temprec;
	int i;
	for (i=0; i<(int)data.size(); i++) {
		temprec  = new MuseRecord;
		*temprec = *(input.data[i]);
		data[i]  = temprec;
	}
	sequence.resize(input.sequence.size());
	for (i=0; i<(int)input.sequence.size(); i++) {
	  sequence[i] = new MuseEventSet;
	  *(sequence[i]) = *(input.sequence[i]);
	}

	name = input.name;
}



//////////////////////////////
//
// MuseData::~MuseData --
//

MuseData::~MuseData() {
	int i;
	for (i=0; i<(int)data.size(); i++) {
		if (data[i] != NULL) {
			delete data[i];
			data[i] = NULL;
		}
	}
  data.resize(0);
  name = "";
}



//////////////////////////////
//
// MuseData::getLineCount -- return the number of lines in the MuseData file.
//

int MuseData::getLineCount(void) {
	return (int)data.size();
}



//////////////////////////////
//
// MuseData::append -- add a MuseRecord to end of file.
//

int MuseData::append(MuseRecord& arecord) {
	MuseRecord* temprec;
	temprec = new MuseRecord;
	*temprec = arecord;
	data.push_back(temprec);
	return (int)data.size()-1;
}


int MuseData::append(MuseData& musedata) {
	int oldsize = (int)data.size();
	int newlinecount = musedata.getLineCount();
	if (newlinecount <= 0) {
		return -1;
	}

	data.resize((int)data.size()+newlinecount);
	for (int i=0; i<newlinecount; i++) {
		data[i+oldsize] = new MuseRecord;
		*(data[i+oldsize]) = musedata[i];
	}
	return (int)data.size()-1;
}


int MuseData::append(string& charstring) {
	MuseRecord* temprec;
	temprec = new MuseRecord;
	temprec->setString(charstring);
	temprec->setType(E_muserec_unknown);
	temprec->setAbsBeat(0);
	data.push_back(temprec);
	return (int)data.size()-1;
}



//////////////////////////////
//
// MuseData::insert -- add a MuseRecord to middle of file.  Not the most
//   efficient, but not too bad as long as the file is not too long, the
//   insertion is close to the end of the file, and you don't use this
//   method to add a set of sequential lines (write a different function
//   for that).
//

void MuseData::insert(int lindex, MuseRecord& arecord) {
	MuseRecord* temprec;
	temprec = new MuseRecord;
	*temprec = arecord;

	data.resize(data.size()+1);
	for (int i=(int)data.size()-1; i>lindex; i--) {
		data[i] = data[i-1];
	}
	data[lindex] = temprec;
}



//////////////////////////////
//
// MuseData::clear --
//

void MuseData::clear(void) {
	for (int i=0; i<(int)data.size(); i++) {
		if (data[i] != NULL) {
			delete data[i];
			data[i] = NULL;
		}
	}
	for (int i=0; i<(int)sequence.size(); i++) {
		sequence[i]->clear();
		delete sequence[i];
		sequence[i] = NULL;
	}
	data.clear();
	sequence.clear();
	name = "";
}



//////////////////////////////
//
// MuseData::operator[] --
//

MuseRecord& MuseData::operator[](int lindex) {
	return *(data[lindex]);
}



//////////////////////////////
//
// MuseData::getRecord --
//

MuseRecord& MuseData::getRecord(int lindex) {
	return *(data[lindex]);
}


//////////////////////////////
//
// MuseData::getRecord -- This version with two index inputs is
//     used to access a data line based on the event time index (time sorted
//     viewpoint) and the particular record index for that event time.
//

MuseRecord& MuseData::getRecord(int eindex, int erecord) {
	return *(data[getEvent(eindex)[erecord].getLineIndex()]);
}



//////////////////////////////
//
// MuseData::read -- read a MuseData file from a file or input stream.
//   0x0a      = unix
//   0x0d      = apple
//   0x0d 0x0a = dos
//

int MuseData::read(istream& input) {
	string dataline;
	dataline.reserve(256);
	int character;
	char value;
	int  isnewline;
	char lastvalue = 0;

	while (!input.eof()) {
		character = input.get();
		if (input.eof()) {
			// end of file found without a newline termination on last line.
			if (dataline.size() > 0) {
				MuseData::append(dataline);
				dataline.clear();
				break;
			}
		}
		value = (char)character;
		if ((value == 0x0d) || (value == 0x0a)) {
			isnewline = 1;
		} else {
			isnewline = 0;
		}
	
		if (isnewline && (value == 0x0a) && (lastvalue == 0x0d)) {
			// ignore the second newline character in a dos-style newline.
			lastvalue = value;
			continue;
		} else {
			lastvalue = value;
		}
	
		if (isnewline) {
			MuseData::append(dataline);
			dataline.clear();
		} else {
			dataline.push_back(value);
		}
	}

	for (int i=0; i<(int)data.size(); i++) {
		data[i]->setLineIndex(i);
	}

	doAnalyses();
	return 1;
}


int MuseData::readFile(const string& filename) {
	ifstream infile(filename);
	return MuseData::read(infile);
}

int MuseData::readString(const string& data) {
	stringstream ss;
	ss << data;
	return MuseData::read(ss);
}



//////////////////////////////
//
// MuseData::doAnalyses --  perform post-processing analysis of the data file
//    (in the correct order).
//

void MuseData::doAnalyses(void) {
	analyzeType();
	analyzeRhythm();
	constructTimeSequence();
	analyzePitch();
	analyzeTies();
}



//////////////////////////////
//
// MuseData::analyzePitch -- calculate the pitch of all notes in terms
//    of their base40 value.
//

void MuseData::analyzePitch() {
	for (int i=0; i<(int)data.size(); i++) {
		data[i]->setMarkupPitch(data[i]->getBase40());
	}
}



//////////////////////////////
//
// MuseData::analyzeTies -- identify which notes are tied to each other.
//

void MuseData::analyzeTies(void) {
	for (int i=0; i<(int)sequence.size(); i++) {
		for (int j=0; j<sequence[i]->getEventCount(); j++) {
			if (!getEvent(i)[j].tieQ()) {
				continue;
			}
			processTie(i, j, -1);
		}
	}
}



//////////////////////////////
//
// MuseData::processTie -- follow a tied note to the last note
//   in the tied sequence, filling in the tie information along the way.
//   Hanging ties (particularly ties note at the ends of first repeats, etc.)
//   still need to be considered.
//

void MuseData::processTie(int eindex, int rindex, int lastindex) {
	int& i = eindex;
	int& j = rindex;


	// lineindex = index of line in original file for the current line.
	int lineindex = getEvent(i)[j].getLineIndex();


	if ((lastindex < 0) &&
		 (data[lineindex]->getLastTiedNoteLineIndex() >= 0)) {
		// If there previously tied note already marked in the data, then
		// this note has already been processed for ties, so exit function
		// without doing any further processing.
		return;
	}

	// store the location of the note tied to previously:
	data[lineindex]->setLastTiedNoteLineIndex(lastindex);

	// If the current note contains a tie marker, then there is
	// another tied note in the future, so go look for it.
	if (!data[lineindex]->tieQ()) {
		data[lineindex]->setNextTiedNoteLineIndex(-1);
		return;
	}

	// There is another note tied to this one in the future, so
	// first get the absolute time location of the future tied note
	HumNum abstime    = data[lineindex]->getAbsBeat();
	HumNum notedur    = data[lineindex]->getNoteDuration();
	HumNum searchtime = abstime + notedur;

	// Get the event index which occurs at the search time:
	int nexteindex = getNextEventIndex(eindex, abstime + notedur);

	if (nexteindex < 0) {
		// Couldn't find any data at that absolute time index, so give up:
		data[lineindex]->setNextTiedNoteLineIndex(-1);
		return;
	}

	// The pitch of the tied note should match this one; otherwise, it
	// would not be a tied note...
	int base40 = data[lineindex]->getPitch();

	// The tied note will preferrably be found in the same track as the
	// current note (but there could be a cross-track tie occurring, so
	// check for that if there is no same-track tie):
	int track = data[lineindex]->getTrack();

	int nextrindex = searchForPitch(nexteindex, base40, track);
	if (nextrindex < 0) {
		// Didn't find specified note at the given event index in the given
		// track, so search for the same pitch in any track at the event time:
		 nextrindex = searchForPitch(nexteindex, base40, -1);
	}
	
	if (nextrindex < 0) {
		// Failed to find a note at the target event time which could be
		// tied to the current note (no pitches at that time which match
		// the pitch of the current note).  This is a haning tie which is
		// either a data error, or is a tie to a note at an earlier time
		// in the music (such as at the beginning of a repeated section).
		// for now just ignore the hanging tie, but probably mark it in
		// some way in the future.
		data[lineindex]->setNextTiedNoteLineIndex(-1);
		return;
	}

	// now the specific note to which this one is tied to is known, so
	// go and process that note:

	int nextindex = getEvent(nexteindex)[nextrindex].getLineIndex();

	data[lineindex]->setNextTiedNoteLineIndex(nextindex);

	processTie(nexteindex, nextrindex, lineindex);
}



//////////////////////////////
//
// MuseData::searchForPitch -- search for a matching pitch in the given
//   track at the specified event index.  If the track is negative, then
//   find the first matching pitch in any track.
//
//   Will also have to separate by category, so that grace notes are
//   searched for separately from regular notes / chord notes, and
//   cue notes as well.
//

int MuseData::searchForPitch(int eventindex, int b40, int track) {
	int targettrack;
	int targetpitch;
	int targettype;

	for (int j=0; j<sequence[eventindex]->getEventCount(); j++) {
		targettype = getEvent(eventindex)[j].getType();
		if ((targettype != E_muserec_note_regular) &&
			 (targettype != E_muserec_note_chord) ) {
			// ignore non-note data (at least ones without durations):
			continue;
		}
		targettrack = getEvent(eventindex)[j].getTrack();
		if ((track >= 0) && (track != targettrack)) {
			continue;
		}
		targetpitch = getEvent(eventindex)[j].getPitch();
		if (targetpitch == b40) {
			return j;
		}
	}

	return -1;
}



//////////////////////////////
//
// MuseData::getNextEventIndex -- return the event index for the given
//   absolute time value.  The starting index is given first, and it
//   is assumed that the target absolute time occurs on or after the
//   starting index value.  Returns -1 if that absolute time is not
//   found in the data (or occurs before the start index.
//

int MuseData::getNextEventIndex(int startindex, HumNum target) {
	int output = -1;
	for (int i=startindex; i<(int)sequence.size(); i++) {
		if (sequence[i]->getTime() == target) {
			output = i;
			break;
		}
	}
	return output;
}


//////////////////////////////
//
// MuseData::last -- return the last record in the data.  Make sure
// that isEmpty() is not true before calling this function.
//

MuseRecord& MuseData::last(void) {
	return (*this)[getNumLines()-1];
}



//////////////////////////////
//
// MuseData::isEmpty -- return true if there are no MuseRecords in the
//    object; otherwise returns true;
//

int MuseData::isEmpty(void) {
	return data.empty();
}



//////////////////////////////
//
// MuseData::analyzeType --
//

void MuseData::analyzeType(void) {
	int commentQ = 0;
	int h = 0;
	MuseData& thing = *this;
	int foundattributes = 0;

	int foundend = 0;

	for (int i=0; i<getNumLines(); i++) {
		if (thing[i].getLength() > 0) {
			if (thing[i][0] == '@') {
				thing[i].setType(E_muserec_comment_line);
				continue;
			}
			if (thing[i][0] == '&') {
				// start or end of multi-line comment;
				commentQ = !commentQ;
				if (!commentQ) {
					thing[i].setType(E_muserec_comment_toggle);
	       continue;
				}
			}
			if (commentQ) {
				thing[i].setType(E_muserec_comment_toggle);
				continue;
			}
		}
		h++;
		if      (h==1)  { thing[i].setType(E_muserec_header_1);  continue; }
		else if (h==2)  { thing[i].setType(E_muserec_header_2);  continue; }
		else if (h==3)  { thing[i].setType(E_muserec_header_3);  continue; }
		else if (h==4)  { thing[i].setType(E_muserec_header_4);  continue; }
		else if (h==5)  { thing[i].setType(E_muserec_header_5);  continue; }
		else if (h==6)  { thing[i].setType(E_muserec_header_6);  continue; }
		else if (h==7)  { thing[i].setType(E_muserec_header_7);  continue; }
		else if (h==8)  { thing[i].setType(E_muserec_header_8);  continue; }
		else if (h==9)  { thing[i].setType(E_muserec_header_9);  continue; }
		else if (h==10) { thing[i].setType(E_muserec_header_10); continue; }
		else if (h==11) { thing[i].setType(E_muserec_header_11); continue; }
		else if (h==12) { thing[i].setType(E_muserec_header_12); continue; }

		if (thing[i].getLength() == 0) {
			thing[i].setType(E_muserec_empty);
			continue;
		}

		if ((h > 12) && (thing[i][0] != '$') && (foundattributes == 0)) {
			thing[i].setType(E_muserec_header_12);
			continue;
		}

		if (foundend && thing[i][0] != '/') {
			thing[i].setType(E_muserec_endtext);
			continue;
		}

		switch (thing[i][0]) {
			case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
			case 'G': thing[i].setType(E_muserec_note_regular);       break;
			case ' ': thing[i].setType(E_muserec_note_chord);         break;
			case 'c': thing[i].setType(E_muserec_note_cue);           break;
			case 'g': thing[i].setType(E_muserec_note_grace);         break;
			case 'P': thing[i].setType(E_muserec_print_suggestion);   break;
			case 'S': thing[i].setType(E_muserec_sound_directives);   break;
			case '/': thing[i].setType(E_muserec_end);
		   foundend = 1;
		   break;
			case 'a': thing[i].setType(E_muserec_append);             break;
			case 'b': thing[i].setType(E_muserec_backspace);          break;
			case 'f': thing[i].setType(E_muserec_figured_harmony);    break;
			case 'i': thing[i].setType(E_muserec_rest_invisible);     break;
			case 'm': thing[i].setType(E_muserec_measure);            break;
			case 'r': thing[i].setType(E_muserec_rest);               break;
			case '*': thing[i].setType(E_muserec_musical_directions); break;
			case '$': thing[i].setType(E_muserec_musical_attributes);
						 foundattributes = 1;
						 break;
		}
	}
}



//////////////////////////////
//
// MuseData::analyzeRhythm -- calulcate the start time in quarter notes
//   for each note/rest in the file.
//
//   Secondary chord notes may or may not have a duration listed.
//   If they do not, then the duration of the note is the same
//   as the primary note of the chord.
//
// char*            getTickDurationField         (char* output);
//

void MuseData::analyzeRhythm(void) {
	HumNum cumulative(0,1);
	HumNum linedur(0,1);
	int tpq = 1;
	HumRegex hre;

	HumNum primarychordnoteduration(0,1);  // needed for chord notes

	for (int i=0; i<(int)data.size(); i++) {
		if (data[i]->getType() == E_muserec_musical_attributes) {
			if (hre.search(data[i]->getLine(), "Q:(\\d+)", "")) {
				tpq = std::stoi(hre.getMatch(1));
			}
		}

		if (data[i]->getType() == E_muserec_note_chord) {
			// insert an automatic back command for chord tones
			// also deal with cue-size note chords?
			data[i]->setAbsBeat(cumulative - primarychordnoteduration);

	 // Check to see if the secondary chord note has a duration.
	 // If so, then set the note duration to that value; otherwise,
	 // set the note duration to the duration of the primary chord
	 // note (first note before the current note which is not a chord
	 // note).
	 string buffer = data[i]->getTickDurationField();
	 if (hre.search(buffer, "\\d", "")) {
				data[i]->setNoteDuration(data[i]->getNoteTickDuration(), tpq);
			} else {
				data[i]->setNoteDuration(primarychordnoteduration);
			}
	 data[i]->setLineDuration(0);
		} else {
			data[i]->setAbsBeat(cumulative);
			data[i]->setNoteDuration(data[i]->getNoteTickDuration(), tpq);
			data[i]->setLineDuration(data[i]->getNoteDuration());
		}
		linedur.setValue(data[i]->getLineTickDuration(), tpq);
		cumulative += linedur;

		switch (data[i]->getType()) {
			case E_muserec_note_regular:
			// should also worry about cue and grace note chords?
			primarychordnoteduration = linedur;
		}
	}

	// adjust Sound and Print records so that they occur at the same
	// absolute time as the note they affect.
	for (int i=1; i<(int)data.size(); i++) {
		switch (data[i]->getType()) {
			case E_muserec_print_suggestion:
			case E_muserec_sound_directives:
				data[i]->setAbsBeat(data[i-1]->getAbsBeat());
		}
	}

}



//////////////////////////////
//
// MuseData::getInitialTPQ -- return the Q: field in the first $ record
//    at the top of the file.
//

int MuseData::getInitialTPQ(void) {
	int output = 0;
	if (data.empty()) {
		return output;
	}
	HumRegex hre;
	int i;
	if (data[0]->getType() == E_muserec_unknown) {
		// search for first line which starts with '$':
		for (i=0; i<(int)data.size(); i++) {
			if (data[i]->getLength() <= 0) {
				continue;
			}
			if ((*data[i])[0] == '$') {
				if (hre.search(data[i]->getLine(), "Q:(\\d+)", "")) {
					output = std::stoi(hre.getMatch(1));
				}
				break;
			}
		}
	} else {
		for (int i=0; i<(int)data.size(); i++) {
			if (data[i]->getType() == E_muserec_musical_attributes) {
				if (hre.search(data[i]->getLine(), "Q:(\\d+)", "")) {
					output = std::stoi(hre.getMatch(1));
				}
				break;
			}
		}
	}

	return output;
}



//////////////////////////////
//
// constructTimeSequence -- Make a list of the lines in the file
//    sorted by the absolute time at which they occur.
//

void MuseData::constructTimeSequence(void) {
	// * clear old event set
	// * allocate the size to match number of lines (* 2 probably).

	MuseData& thing = *this;
	for (int i=0; i<(int)data.size(); i++) {
		insertEventBackwards(thing[i].getAbsBeat(), &thing[i]);
	}
}



///////////////////////////////
//
// MuseData::getEventCount -- returns the number of unique times
//    at which data line occur in the file.
//

int MuseData::getEventCount(void) {
	return (int)sequence.size();
}



///////////////////////////////
//
// MuseData::getEvent --
//

MuseEventSet& MuseData::getEvent(int eindex) {
	return *(sequence[eindex]);
}



///////////////////////////////////////////////////////////////////////////
//
// private functions
//



//////////////////////////////
//
// MuseData::insertEventBackwards -- insert an event into a time-sorted
//    organization of the file. Searches for the correct time location to
//    insert event starting at the end of the list (since MuseData files
//    are mostly sorted in time.
//
//

void printSequenceTimes(vector<MuseEventSet*>& sequence) {
	for (int i=0; i<(int)sequence.size(); i++) {
		cout << sequence[i]->getTime().getFloat() << " ";
	}
	cout << endl;
}


void MuseData::insertEventBackwards(HumNum atime, MuseRecord* arecord) {

	if (sequence.empty()) {
		MuseEventSet* anevent = new MuseEventSet;
		anevent->setTime(atime);
		anevent->appendRecord(arecord);
		sequence.push_back(anevent);
		return;
	}

	for (int i=(int)sequence.size()-1; i>=0; i--) {
		if (sequence[i]->getTime() == atime) {
			sequence[i]->appendRecord(arecord);
			return;
		} else if (sequence[i]->getTime() < atime) {
			// insert new event entry after the current one since it occurs later.
			MuseEventSet* anevent = new MuseEventSet;
			anevent->setTime(atime);
			anevent->appendRecord(arecord);
			if (i == (int)sequence.size()-1) {
				// just append the event at the end of the list
				sequence.push_back(anevent);
	    return;
			} else {
				// event has to be inserted before end of list, so move
				// later ones up in list.
				sequence.resize(sequence.size()+1);
				for (int j=(int)sequence.size()-1; j>i+1; j--) {
					sequence[j] = sequence[j-1];
				}
				// store the newly created event entry in sequence:
				sequence[i+1] = anevent;
				return;
			}
		}
	}
	cerr << "FUNNY ERROR OCCURED at time " << atime << endl;
	exit(1);
}


//////////////////////////////
//
// MuseData::getTiedDuration -- these version acess the record lines
//    via the time-sorted event index.
//

HumNum MuseData::getTiedDuration(int eindex, int erecord) {
	return getTiedDuration(getLineIndex(eindex, erecord));
}



//////////////////////////////
//
// MuseData:getTiedDuration --
//

HumNum MuseData::getTiedDuration(int index) {
	HumNum output(0,1);

	// if the line is not a regular/chord note with duration, then
	// return the duration field.
	if ((getRecord(index).getType() != E_muserec_note_chord) &&
		 (getRecord(index).getType() != E_muserec_note_regular) ) {
		return output;
	}

	// if the note is tied to a previous note, then return a
	// duration of 0 (behavior may change in the future).
	if (getRecord(index).getLastTiedNoteLineIndex() >= 0) {
		return output;
	}

	// if the note is not tied to anything into the future, then
	// gives it actual duration
	if (getRecord(index).getNextTiedNoteLineIndex() < 0) {
		return getRecord(index).getNoteDuration();
	}
	
	// this is start of a group of tied notes.  Start figuring out
	// how long the duration of the tied group is.
	output = getRecord(index).getNoteDuration();
	int myindex = index;
	while (getRecord(myindex).getNextTiedNoteLineIndex() >= 0) {
		myindex = getRecord(myindex).getNextTiedNoteLineIndex();
		output += getRecord(myindex).getNoteDuration();
	}

	return output;
}



//////////////////////////////
//
// MuseData::getLineIndex -- return the line number of a particular
//    event/record index pair (the line index is the same as the index
//    into the list of lines).
//

int MuseData::getLineIndex(int eindex, int erecord) {
	return getRecord(eindex, erecord).getLineIndex();
}



//////////////////////////////
//
// MuseData::getLineDuration -- return the duration of an isolated line.
//

HumNum MuseData::getLineDuration(int eindex, int erecord) {
	return getRecord(eindex, erecord).getLineDuration();
}



//////////////////////////////
//
// MuseData::getNoteDuration -- return the duration of an isolated note.
//

HumNum MuseData::getNoteDuration(int eindex, int erecord) {
	return getRecord(eindex, erecord).getNoteDuration();
}



//////////////////////////////
//
// MuseData::getLastTiedNoteLineIndex -- return the line index of the
//     previous note to which this one is tied to.  Returns -1 if there
//     is no previous tied note.
//

int MuseData::getLastTiedNoteLineIndex(int eindex, int erecord) {
	return getRecord(eindex, erecord).getLastTiedNoteLineIndex();
}



//////////////////////////////
//
// MuseData::getNextTiedNoteLineIndex -- returns the line index of the
//    next note to which this one is tied to.  Returns -1 if there
//    is no previous tied note.
//

int MuseData::getNextTiedNoteLineIndex(int eindex, int erecord) {
	return getRecord(eindex, erecord).getNextTiedNoteLineIndex();
}



//////////////////////////////
//
// MuseData::getType -- return the record type of a particular event
//     record.
//

int MuseData::getType(int eindex, int erecord) {
	return getRecord(eindex, erecord).getType();
}



//////////////////////////////
//
// MuseData::getAbsBeat -- return the absolute beat time (quarter
//    note durations from the start of the music until the current
//    object.
//

HumNum MuseData::getAbsBeat(int lindex) {
	return data[lindex]->getAbsBeat();
}



//////////////////////////////
//
// MuseData::getLineTickDuration --
//

int MuseData::getLineTickDuration(int lindex) {
	return data[lindex]->getLineTickDuration();
}


//////////////////////////////
//
// MuseData::setFilename --
//

void MuseData::setFilename(const string& filename) {
	name = filename;
}



//////////////////////////////
//
// MuseData::getFilename --
//

string MuseData::getFilename(void) {
	return name;
}



//////////////////////////////
//
// MuseData::getPartName -- return
//

string MuseData::getPartName(void) {
	int line = getPartNameIndex();
	if (line < 0) {
		return "";
	}
	HumRegex hre;
	string output = data[line]->getLine();
	hre.replaceDestructive(output, "", "^\\s+");
	hre.replaceDestructive(output, "", "\\s+$");
	return output;
}



//////////////////////////////
//
// MuseData::getPartNameIndex -- Search for the part name in the header.
//    search the entire file if it is missing (which it should not be.
//

int MuseData::getPartNameIndex(void) {
	int output = -1;
	for (int i=0; i<(int)data.size(); i++) {
		if (data[i]->getType() == E_muserec_header_part_name) {
			return i;
		}
	}
	return output;
}



//////////////////////////////
//
// MuseData::isMember -- returns true if the file belongs to the
//     given membership string.  Example memberships are "score",
//     "skore", "part", "sound".
//

int MuseData::isMember(const string& mstring) {
	for (int i=0; i<(int)data.size(); i++) {
		if (data[i]->getType() == E_muserec_group_memberships) {
			if (strstr(data[i]->getLine().c_str(), mstring.c_str()) != NULL) {
				return 1;
			} else {
				return 0;
			}
		}
		if (data[i]->getType() == E_muserec_musical_attributes) {
			break;
		}
	}
	return 0;
}



//////////////////////////////
//
// MuseData::getMembershipPartNumber -- returns the part number within
//     a given membership for the data.
// Example:
//     sound: part 1 of 4
//  in this case the value returned is 1.
//

int MuseData::getMembershipPartNumber(const string& mstring) {
	string searchstring = "^";
	searchstring += mstring;
	searchstring += ":";

	HumRegex hre;
	for (int i=0; i<(int)data.size(); i++) {
		if (data[i]->getType() == E_muserec_header_12) {
			if (hre.search(data[i]->getLine(), searchstring, "")) {
				if (hre.search(data[i]->getLine(),
					"part\\s*(\\d+)\\s*of\\s*(\\d+)")) {
					string partnum = hre.getMatch(1);
					return std::stoi(partnum);
				}
			}
		}
		if (data[i]->getType() == E_muserec_musical_attributes) {
			break;
		}
	}
	return 0;
}



////////////////////////////////
//
// MuseData::selectMembership --
//

void MuseData::selectMembership(const string& selectstring) {
	if (!isMember(selectstring)) {
		// not a member of the given membership, so can't select that
		// membership.
		return;
	}
	string buffer;
	buffer = "Group memberships: ";
	buffer += selectstring;

	for (int i=0; i<getNumLines(); i++) {
		if ((*this)[i].getType() == E_muserec_group_memberships) {
			(*this)[i].setLine(buffer);
		} else if ((*this)[i].getType() == E_muserec_header_12) {
			if (strncmp((*this)[i].getLine().c_str(), selectstring.c_str(),
					selectstring.size()) != 0) {
				(*this)[i].setType(E_muserec_deleted);
			}
		}
	}


}



///////////////////////////////
//
// MuseData::cleanLineEndings -- remove spaces at the end of lines
//

void MuseData::cleanLineEndings(void) {
	for (int i=0; i<this->getLineCount(); i++) {
		(*this)[i].cleanLineEnding();
	}
}



///////////////////////////////////////////////////////////////////////////
//
// friendly functions
//


//////////////////////////////
//
// operator<< --
//

ostream& operator<<(ostream& out, MuseData& musedata) {
	for (int i=0; i<musedata.getLineCount(); i++) {
		if (musedata[i].getType() != E_muserec_deleted) {
			out << musedata[i].getLine() << (char)0x0d << (char)0x0a;
		}
	}
	return out;
}


// END_MERGE

} // end namespace hum


