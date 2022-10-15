#ifndef TIMER_HPP
#define TIMER_HPP

class Timer
{
  public:

    Timer() {
        Ticks = 0;
        Started = false;
    }

		void start() {
      Started = true;
      Ticks = SDL_GetTicks();
    }

		void stop() {
      Started = false;
    	Ticks = 0;
    }

		// Get elapsed time
		Uint32 getTicks() {
    	Uint32 time = 0;

      if( Started )
        time = SDL_GetTicks() - Ticks;

      return time;
    }

		bool isStarted(){ return Started; }

  private:
		Uint32 Ticks;
		bool Started;
};

#endif
