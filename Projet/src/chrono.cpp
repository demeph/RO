#include "chrono.h"

chrono::chrono()
{}

void chrono::start()
{
	struct rusage rusage;
	
	getrusage(RUSAGE_SELF, &rusage);
	start_utime_ = rusage.ru_utime;
}

void chrono::stop()
{
    struct rusage rusage;
	
	getrusage(RUSAGE_SELF, &rusage);
	stop_utime_ = rusage.ru_utime;
}

double chrono::to_ms() const
{
    return (stop_utime_.tv_sec - start_utime_.tv_sec) * 1000 +
           (stop_utime_.tv_usec - start_utime_.tv_usec) / 1000;
}
