#pragma once
class Time {
	//days
	int days;

	//hours
	int hours;

public:
	//constructor
	Time() :days(0), hours(0)
	{}
	Time(int d, int h)
	{
		calculateTime(d, h);
	}

	//getters
	int gethour() const
	{
		return hours;
	}
	int getDays()const
	{
		return days;
	}
	//setters
	void settime(int d, int h)
	{
		calculateTime(d, h);
	}
	//converts hours and days to Time (same as set time)
	void calculateTime(int d, int h)
	{
		if (h > 23)
		{
			hours = h - 23;
			days = ++d; //check on postfix and prefix
		}

		else
		{
			days = d;
			hours = h;
		}

	}

	//operators overloading functions
	void operator ++(int)
	{
		int h2;
		h2 = ++hours;
		calculateTime(days, h2);

	}

	bool operator >=(const Time& t2)
	{
		//calling object's days andhours
		int d1 = days;
		int h1 = hours;
		//passed object days and hours
		int d2 = t2.getDays();
		int h2 = t2.gethour();

		if ((d1 == d2 && h1 == h2) || (d1 > d2) || (d1 == d2 && h1 > h2))
		{
			return true;
		}
		return false;


	}
	bool operator >(const Time& t2)
	{
		//calling object's days andhours
		int d1 = days;
		int h1 = hours;
		//passed object days and hours
		int d2 = t2.getDays();
		int h2 = t2.gethour();

		if ((d1 > d2) || (d1 == d2 && h1 > h2))
		{
			return true;
		}
		return false;


	}
	bool operator <(const Time& t2)
	{
		//calling object's days andhours
		int d1 = days;
		int h1 = hours;
		//passed object days and hours
		int d2 = t2.getDays();
		int h2 = t2.gethour();

		if ((d1 < d2) || (d1 == d2 && h1 < h2))
		{
			return true;
		}
		return false;


	}
	bool operator == (const Time& t2)
	{
		//calling object's days andhours
		int d1 = days;
		int h1 = hours;
		//passed object days and hours
		int d2 = t2.getDays();
		int h2 = t2.gethour();
		if (d1 == d2 && h1 == h2)
			return true;
		return false;
	}
	bool operator <=(const Time& t2) {
		//calling object's days andhours
		int d1 = days;
		int h1 = hours;
		//passed object days and hours
		int d2 = t2.getDays();
		int h2 = t2.gethour();
		if (d1 <= d2 || d1 == d2 && h1 <= h2) return true;
		else return false;

	}
	Time operator +(const Time& t1)
	{
		int d1 = t1.getDays();
		int h1 = t1.gethour();
		calculateTime(d1 + days, h1 + hours);
		return Time(days, hours);

	}
	Time operator -(const Time& t1)
	{
		int d1 = t1.getDays();
		int h1 = t1.gethour();
		calculateTime(days - d1, hours - h1);

		return Time(days, hours); // we must check that days and hourss aren't -ve(to be done)

	}
	/*/bool operator==(const Time& T2) {
		if (this->hours == T2.hours && this->days == T2.days) return true;
		else return false;
	}*/
	Time& operator =(const Time& T2)
	{
		this->hours = T2.hours;
		this->days = T2.days;
		return *this;
	}
};
