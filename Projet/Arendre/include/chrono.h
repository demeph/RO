#ifndef JAPH_CHRONO
#define JAPH_CHRONO

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h> /* Bibliothèques utilisées pour mesurer le temps CPU */

class chrono
{
  public:
    chrono();
    void start();
    void stop();
    double to_ms() const;
    double to_sec() const;

  private:
    timeval start_utime_;
    timeval stop_utime_;
};

#endif//JAPH_CHRONO
