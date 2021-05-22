#ifndef WORDCLOCK_GRID_LANG_EN_EN_H
#define WORDCLOCK_GRID_LANG_EN_EN_H

class Grid_en_EN {
	public:
	static int time_it_is[5];
	static int time_minutes[12][15];
	static int time_hours[12][6];
	static int time_day[6][14];
	static int time_day_ix;
	static int minuteix;
	static void setTime(int hour, int minute);
};

typedef class Grid_en_EN Grid;

#endif
