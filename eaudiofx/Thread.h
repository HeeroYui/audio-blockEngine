/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */


#ifndef __EAUDIO_FX_THREAD_H__
#define __EAUDIO_FX_THREAD_H__

#include <thread>
#include <mutex>
#include <etk/os/Fifo.h>
#include <eaudiofx/core/audio.h>

/**
 * @brief Tanho thread system (parent class)
 */
namespace eaudiofx {
	enum status {
		statusNotStarted, //!< The thread is creating itself
		statusCreating, //!< The thread is creating itself
		statusStart, //!< The element is starting
		statusRun, //!< The thread is running
		statusStop, //!< The thread is stoping
		statusDie, //!< the thread is diing or dead
	};
	class Thread {
		private:
			static void genericThreadCall(void * data);
		protected:
			std::shared_ptr<std::thread> m_thread;
			std::mutex m_interfaceMutex;
			int32_t m_flags;
		public:
			Thread(const std::string& _name="not-set-name");
			~Thread();
			int32_t start(); //!< start the thread
			int32_t stop(); //!< stop this current thread (request the stop of the process) ==> a-synchronous request
			int32_t stopAtEnd(); //!< stop when the process is ended (when possible) ==> stop and wait hte real end of the thread
			void setRepeating(int32_t delayBetweenRestart, int32_t maxTimeRestart); //!< configure repeating
			void setNoRepeating(); //!< cancel SetRepeating
		protected:
			void threadCall(); //!< internal call of  sup thread system (call from GenericThreadCall)
		private:
			void threadChangeState(enum status _newState); //!< information about state change
		protected:
			std::string m_name; //!< curent thread name
		private:
			uint32_t m_id; //!< Thread Id it will be Unique
			enum status m_state; //!< Thread current state
		protected:
			enum status getState() {
				return m_state;
			};
			/**
			 * @brief Thread state "Start" process
			 * @return true if an error occured ==> this kill the thread.
			 */
			virtual bool stateStart();
			/**
			 * @brief Thread state "Run" process
			 * @return true if an error occured or a kill is requested by a block
			 */
			virtual bool stateRun();
			/**
			 * @brief Thread state "Stop" process
			 * @return true if an error occured
			 */
			virtual bool stateStop();
	};
};

#endif