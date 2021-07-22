#ifndef Utils
#define Utils
#include <time.h>
#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

namespace nc{
	void sleep(int sec=1,int msec=0,int mcrsec=0,int nsec=0){
		struct timespec tim, tim2;
		tim.tv_sec=sec;
		tim.tv_nsec=nsec+(((msec*1000)+mcrsec)*1000);

		if(nanosleep(&tim , &tim2)<0){
			throw -1;
		}
	}
	
	class TimeTracker{
	public:
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;
		duration<double, std::milli> timeTime;
		bool ended;
		TimeTracker(): ended(false){}

		void start(){
			startTime=high_resolution_clock::now();
			ended=false;
		}

		void end(){
			endTime=high_resolution_clock::now();
			timeTime=endTime-startTime;
			ended=true;
		}

		double time(){
			if (ended){
				return timeTime.count();
			}else{
				return -1;
			}
		}
	};

	class TimeLimiter{
		double limitTime;
		TimeTracker tracker;
		TimeLimiter(double time):limitTime(time){}

		void start(){
			tracker.start();
		}

		void end(){
			tracker.end();
		}

		void delay(){
			double sleepTime=tracker.time()-limitTime*1000*1000;
			sleepTime= sleepTime>0 ? sleepTime : 0;

			int sleepTimeMs=sleepTime;
			int sleepTimeMcrs=(sleepTime-((double)sleepTimeMs))*1000;

			nc::sleep(0,sleepTimeMs,sleepTimeMcrs,0);
		}
	};
}

#undef high_resolution_clock
#undef duration_cast
#undef duration
#undef milliseconds

#endif