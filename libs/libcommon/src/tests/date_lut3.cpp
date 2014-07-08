#include <iostream>

#include <Poco/Exception.h>

#include <Yandex/DateLUT.h>
#include <Yandex/time2str.h>


void loop(time_t begin, time_t end, int step)
{
	DateLUT & date_lut = DateLUT::instance();
	
	for (time_t t = begin; t < end; t += step)
	{
		time_t t2 = date_lut.makeDateTime(date_lut.toYear(t), date_lut.toMonth(t), date_lut.toDayOfMonth(t),
			date_lut.toHourInaccurate(t), date_lut.toMinute(t), date_lut.toSecond(t));

		std::string s1 = Time2Sql(t);
		std::string s2 = Time2Sql(t2);
			
		std::cerr << s1 << ", " << s2 << std::endl;
		
		if (s1 != s2)
			throw Poco::Exception("Test failed.");
	}
}


int main(int argc, char ** argv)
{
	loop(OrderedIdentifier2Date(20101031), OrderedIdentifier2Date(20101101), 15 * 60);
	loop(OrderedIdentifier2Date(20100328), OrderedIdentifier2Date(20100330), 15 * 60);

	return 0;
}
