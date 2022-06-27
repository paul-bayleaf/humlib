//
// Programmer:    Kiana Hu
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Mon Feb 28 11:14:20 PST 2022
// Last Modified: Sat May 14 12:47:09 PDT 2022
// Filename:      tool-cmr.h
// URL:           https://github.com/craigsapp/humlib/blob/master/include/tool-cmr.h
// Syntax:        C++11; humlib
// vim:           ts=3 noexpandtab
//
// Description:   Analyze conspicuous melodic repetitions.
//

#ifndef _TOOL_PEAK_H
#define _TOOL_PEAK_H

#include "HumTool.h"
#include "HumdrumFile.h"

namespace hum {

// START_MERGE

class cmr_note_info {

	public:
		cmr_note_info(void) {
			clear();
		}

		void clear(void) {
			m_cmrPitch       = NULL;
			m_hasSyncopation = false;
			m_hasLeapBefore  = false;
			m_measureBegin= -1;
			m_measureEnd  = -1;
		}

		int getMeasureBegin(void) {
			return m_measureBegin;
		}

		int getMeasureEnd(void) {
			return m_measureEnd;
		}

		HumNum getStartTime(void) {
			return m_cmrPitch->getDurationFromStart();
		}

		HumNum getEndTime(void) {
			HumNum noteDur = m_cmrPitch->getTiedDuration();
			return m_cmrPitch->getDurationFromStart() + noteDur;
		}

		int getMidiPitch(void) {
			return m_cmrPitch->kernToMidiNoteNumber();
		}

		double getNoteStrength(void) {
			double output = 1.0;
			if (m_hasSyncopation) {
				output += m_syncopationWeight;
			}
			if (m_hasLeapBefore) {
				output += m_leapWeight;
			}
			return output;
		}

	public:
		static double m_syncopationWeight;
		static double m_leapWeight;

		HTp   m_cmrPitch;        // pitches of the cmr sequence (excluding tied notes)
		bool  m_hasSyncopation;  // is the note syncopated
		bool  m_hasLeapBefore;   // is there a melodic leap before note
		int   m_measureBegin; // starting measure of note
		int   m_measureEnd;   // ending measure of tied note group

};


class cmr_group_info {
	public:
		cmr_group_info(void) {
			clear();
		}

		void clear(void) {
			m_cmrIndex  = -1;
			m_cmrTrack  = -1;
			m_startTime = -1;
			m_endTime   = -1;
			m_notes.clear();
		}

		int getNoteCount(void) {
			if (m_cmrIndex < 0) {
				return 0;
			}
			return m_notes.size();
		}

		HumNum getGroupDuration(void) {
			if (m_notes.empty()) {
				return 0;
			}
			HumNum startPos = m_notes[0].m_cmrPitch->getDurationFromStart();
			HumNum endPos   = m_notes.back().m_cmrPitch->getDurationFromStart();
			return endPos - startPos;
		}

		int getMeasureBegin(void) {
			if (m_notes.empty()) {
				return -1;
			}
			return m_notes[0].getMeasureBegin();
		}

		int getMeasureEnd(void) {
			if (m_notes.empty()) {
				return -1;
			}
			return m_notes.back().getMeasureEnd();
		}

		HumNum getStartTime(void) {
			if (m_notes.empty()) {
				return -1;
			}
			return m_notes[0].getStartTime();
		}

		HumNum getEndTime(void) {
			if (m_notes.empty()) {
				return -1;
			}
			return m_notes.back().getStartTime();
		}

		int getMidiPitch(void) {
			if (m_notes.empty()) {
				return -1;
			}
			return m_notes.getMidiPitch();
		}

		double getGroupStrength(void) {
			double output = 0.0;
			for (int i=0; i<(int)m_notes.size(); i++) {
				output += m_notes[i].getNoteStrength();
			}
			return output;
		}

		void mergeGroup(cmr_group_info& group) {
		for (int i=0; i<(int)m_cmrPitch[index2].size(); i++) { //not updated from here down
			vector<HTp> newtoks;
			newtoks.clear();
			for (int j=0; j<(int)m_cmrPitch[index1].size(); j++) {
				HTp token1 = m_cmrPitch[index1][j];
				HTp token2 = m_cmrPitch[index2][i];
				if (token2 == NULL) {
					continue;
				}
				if (token1 == token2) {
					m_cmrPitch[index2][i] = NULL;
				}
			}
		}

		// Deactivate the second group by setting a negative index:
		m_noteGroups[index2].m_cmrIndex *= -1;

		for (int k=0; k<(int)m_cmrPitch[index2].size(); k++) {
			HTp token = m_cmrPitch[index2][k];
			if (!token) {
				continue;
			}
			m_cmrPitch[index1].push_back(token);
		}

		m_cmrPeakCount[index1] = m_cmrPitch[index1].size();

		return true;
	}

		int   m_cmrIndex;    // used to keep track of mergers
		int   m_cmrTrack;    // used to keep track of mergers
		std::vector<cmr_note_info> m_notes; // note info for each note in group.
};



class Tool_cmr : public HumTool {
	public:
		                 Tool_cmr                (void);
		                ~Tool_cmr                () {};

		bool             run                     (HumdrumFileSet& infiles);
		bool             run                     (HumdrumFile& infile);
		bool             run                     (const string& indata, ostream& out);
		bool             run                     (HumdrumFile& infile, ostream& out);

	protected:
		void             processFile             (HumdrumFile& infile);
		void             initialize              (void);
		void             processFile             (HumdrumFile& infile, Options& options);
		void             processSpine            (HTp startok);
		void             processSpineFlipped     (HTp startok);
		void             identifyLocalPeaks      (std::vector<bool>& cmrnotes,
		                                          std::vector<int>& notelist);
		void             getDurations            (vector<double>& durations,
		                                          vector<vector<HTp>>& notelist);
		void             getBeat                 (vector<bool>& metpos,
		                                          vector<vector<HTp>>& notelist);
		int              getMetricLevel          (HTp token);
		bool             isMelodicallyAccented   (HTp token);
		bool             hasLeapBefore           (HTp token);
		bool             isSyncopated            (HTp token);
		void             getLocalPeakNotes       (vector<vector<HTp>>& newnotelist,
		                                          vector<vector<HTp>>& oldnotelist,
		                                          vector<bool>& cmrnotes);

		void             identifyPeakSequence    (vector<bool>& globalcmrnotes,
		                                          vector<int>& cmrmidinums,
		                                          vector<vector<HTp>>& notes);
		std::vector<int> getMidiNumbers          (std::vector<std::vector<HTp>>& notelist);
		std::vector<std::vector<HTp>> getNoteList(HTp starting);
		void             printData               (std::vector<std::vector<HTp>>& notelist,
		                                          std::vector<int>& midinums,
		                                          std::vector<bool>& cmrnotes);
		void             markNotesInScore        (vector<vector<HTp>>& cmrnotelist,
		                                          vector<bool>& iscmr);
		void             mergeOverlappingPeaks   (void);
		bool             checkGroupPairForMerger (int index1, int index2);
		int              countNotesInScore       (HumdrumFile& infile);
		std::vector<int> flipMidiNumbers         (vector<int>& midinums);
		void             markNotes               (vector<vector<HTp>>& notelist, vector<bool>& cmrnotesQ,
		                                          const string& marker);
		void             postProcessAnalysis     (HumdrumFile& infile);

	private:
		bool    m_rawQ        = false;           // don't print score (only analysis)
		bool    m_cmrQ        = false;           // analyze only cmrs
		bool    m_ncmrQ       = false;           // analyze only negative cmrs (troughs)
		bool    m_naccentedQ  = false;           // analyze cmrs without melodic accentation
		bool    m_infoQ       = false;           // used with -i option: display info only
		bool    m_localQ      = false;           // used with -l option: mark all local peaks
		bool    m_localOnlyQ  = false;           // used with -L option: only mark local peaks, then exit before CMR analysis.

		double  m_smallRest   = 4.0;             // Ignore rests that are 1 whole note or less
		double  m_cmrDur      = 24.0;            // 6 whole notes maximum between m_cmrNum local maximums
		double  m_cmrNum      = 3;               // number of local maximums in a row needed to mark in score

		int     m_count       = 0;               // number of cmr sequences in score
		int     m_noteCount   = 0;               // total number of notes in the score

		std::string m_color     = "red";         // color to mark cmr notes
		std::string m_marker    = "@";           // marker to label cmr notes in score

		std::string m_local_color = "limegreen"; // color to mark local peaks
		std::string m_local_marker = "N";        // marker for local peak notes
		int         m_local_count = 0;           // used for coloring local peaks

		// negative peak markers:
		std::string m_local_color_n = "green";   // color to mark local peaks
		std::string m_local_marker_n = "K";      // marker for local peak notes
		int         m_local_count_n = 0;         // used for coloring local peaks

		std::string m_leap_color  = "purple";    // color to mark leap notes before peaks
		std::string m_leap_marker = "k";         // marker for leap notes

		std::vector<int>    m_barNum;            // storage for identify start/end measures of cmr groups

		// m_noteGroups: 2D:
		// dimension 1 == a note group
		// dimension 2 == m_noteGroups.m_notesa == notes in specified group
		// m_noteGroups[2].m_notes[5] == 3rd group, 6th note in the 3rd group
		std::vector<cmr_group_info> m_noteGroups;

// remove these variables:
		// m_cmrMeasureBegin ->   m_noteGroups[i].m_notes[j].m_cmrMeasureBegin;
		std::vector<int>    m_cmrMeasureBegin;   // starting measure of cmr group
		// m_cmrMeasureEnd ->   m_noteGroups[i].m_notes[j].m_cmrMeasureEnd;
		std::vector<int>    m_cmrMeasureEnd;     // starting measure of cmr group
		// m_noteGroups[i].getDuration();
		std::vector<HumNum> m_cmrDuration;       // between first cmr note and last cmr note.
		// m_noteGroups[i].m_notes[j].m_cmrPitch;
		std::vector<std::vector<HTp>> m_cmrPitch;// pitches of the cmr sequence (excluding tied notes)
		// (int)m_noteGroups[i].m_notes.size();
		std::vector<int>    m_cmrPeakCount;      // how many notes in a cmr sequence

// remove these variables also:
		// Merging variables for cmr groups:
		// m_cmrIndex ->  m_notesGroups[i].m_cmrIndex;
		std::vector<int>    m_cmrIndex;          // used to keep track of mergers
		// m_cmrIndex ->  m_notesGroups[i].m_cmrTrack;
		std::vector<int>    m_cmrTrack;          // used to keep track of mergers
		// m_cmrIndex ->  m_notesGroups[i].m_StartTime;
		std::vector<HumNum> m_startTime;         // starting time of first note in group
		// m_cmrIndex ->  m_notesGroups[i].m_endTime;
		std::vector<HumNum> m_endTime;           // ending time of last note in group

};

// END_MERGE

} // end namespace hum

#endif /* _TOOL_PEAK_H */
