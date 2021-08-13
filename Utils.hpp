#ifndef Utils
#define Utils
#include <time.h>
#include <chrono>

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
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
		std::chrono::duration<double, std::milli> timeTime;
		bool ended;
		TimeTracker(): ended(false){}

		void start(){
			startTime=std::chrono::high_resolution_clock::now();
			ended=false;
		}

		void end(){
			endTime=std::chrono::high_resolution_clock::now();
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
	public:
		long double time;
		TimeTracker tracker;
		TimeLimiter(long double time):time(time){} //time is in ms

		void start(){
			tracker.start();
		}

		void end(){
			tracker.end();
		}

		void delay(){
			double sleepTime=time-(tracker.time());
			sleepTime= sleepTime>0 ? sleepTime : 0;

			int sleepTimeMs=sleepTime;
			int sleepTimeMcrs=(sleepTime-(int)sleepTime)*1000;

			nc::sleep(0,sleepTimeMs,sleepTimeMcrs,0);
		}
	};
}

#endif