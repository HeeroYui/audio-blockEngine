/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#include <audio/blockEngine/debug.hpp>
#include <audio/blockEngine/Thread.hpp>
#include <unistd.h>


static const char* threadGetCharState(enum audio::blockEngine::status state) {
	const char* ret = (const char*)"";
	switch (state) {
		case audio::blockEngine::statusNotStarted:
			ret = (const char*)"NOT_STARTED";
			break;
		case audio::blockEngine::statusCreating:
			ret = (const char*)"CREATING";
			break;
		case audio::blockEngine::statusStart:
			ret = (const char*)"START";
			break;
		case audio::blockEngine::statusRun:
			ret = (const char*)"RUN";
			break;
		case audio::blockEngine::statusStop:
			ret = (const char*)"STOP";
			break;
		case audio::blockEngine::statusDie:
			ret = (const char*)"DIE";
			break;
		default:
			ret = (const char*)"???";
			break;
	}
	return ret;
}

/**
 * @brief change the current state of the thread.
 * @param[in] _newState The new state for the thread.
 */
void audio::blockEngine::Thread::threadChangeState(enum audio::blockEngine::status _newState) {
	int ret;
	std::unique_lock<std::mutex> lock(m_interfaceMutex);
	// debug display :
	ABE_DEBUG("[" << m_id << "] '" << m_name << "' Change state : " << threadGetCharState(m_state) << " ==> " << threadGetCharState(_newState));
	// set the New state
	m_state = _newState;
	return;
}


audio::blockEngine::Thread::Thread(const std::string& _chainName) {
	if (_chainName != "") {
		m_name = _chainName;
	} else {
		m_name = "No-name";
		ABE_WARNING("the thread has no name");
	}
	static int32_t threadIDBasic = 100;
	m_id = threadIDBasic++;
	ABE_INFO("THREAD : Allocate [" << m_id << "] name='" << m_name << "'");
	m_state = audio::blockEngine::statusNotStarted;
}


audio::blockEngine::Thread::~Thread() {
	ABE_INFO("THREAD : Destroy [" << m_id << "] name='" << m_name << "'");
	stop();
	m_thread->join();
	m_thread.reset();
}


int32_t audio::blockEngine::Thread::start() {
	int ret;
	if (audio::blockEngine::statusDie == m_state) {
		ABE_INFO("Thread [" << m_id << "] name='" << m_name << "' ==> state die ... ==> delete it ...");
		stopAtEnd();
	}
	if (audio::blockEngine::statusNotStarted != m_state) {
		ABE_ERROR("Failed to create [" << m_id << "] name='" << m_name << "' ==> the thread is not stopped ...");
		return audio::blockEngine::ERR_FAIL;
	}
	m_state = audio::blockEngine::statusCreating;
	m_thread = std::make_shared<std::thread>(audio::blockEngine::Thread::genericThreadCall, reinterpret_cast<void*>(this));
	// no else ==> the thread is started corectly... (we think)
	return audio::blockEngine::ERR_NONE;
}

int32_t audio::blockEngine::Thread::stop() {
	ABE_INFO(" Stop [" << m_id << "] name='" << m_name << "'");
	// Set the stop flag for the thread :
	std::unique_lock<std::mutex> lock(m_interfaceMutex);
	m_flags |= 1;
	return audio::blockEngine::ERR_NONE;
}


int32_t audio::blockEngine::Thread::stopAtEnd() {
	int systemRet;
	int32_t ret = audio::blockEngine::ERR_NONE;

	ABE_INFO(" Delete [" << m_id << "] name='" << m_name << "' (StopAtEnd)");
	
	// Request the thread stop:
	ret = stop();
	if (audio::blockEngine::ERR_NONE != ret) {
		ABE_ERROR("The thread have a problem to stop");
		return ret;
	}
	if (audio::blockEngine::statusNotStarted != m_state) {
		m_thread.reset();
	}
	std::unique_lock<std::mutex> lock(m_interfaceMutex);
	m_flags = 0;
	
	m_state = audio::blockEngine::statusNotStarted;
	return ret;
}

// function that might be writen for every thread
bool audio::blockEngine::Thread::stateStart() {
	ABE_DEBUG("Not overwrited in the herited classes: StateStart");
	// virtual function ...
	return false;
}

bool audio::blockEngine::Thread::stateRun() {
	ABE_DEBUG("Not overwrited in the herited classes: StateRun");
	// virtual function ...
	usleep(100000);
	// Force the stop if this function is not overwritte
	return false;
}


bool audio::blockEngine::Thread::stateStop() {
	ABE_DEBUG("Not overwrited in the herited classes: StateStop");
	// virtual function ...
	return false;
}

void audio::blockEngine::Thread::genericThreadCall(void* _data) {
	audio::blockEngine::Thread * self = reinterpret_cast<audio::blockEngine::Thread*>(_data);
	if (self != nullptr) {
		self->threadCall();
	} else {
		ABE_ERROR("can not start th ethraead ...");
	}
}

void audio::blockEngine::Thread::threadCall() {
	bool autoKill = false;
	// Endless loop.
	while(audio::blockEngine::statusDie != m_state) {
		int32_t flags = 0;
		{
			std::unique_lock<std::mutex> lock(m_interfaceMutex);
			flags = m_flags;
			m_flags = 0;
		}
		if (flags == 1 ) {
			ABE_DEBUG("Detect stop request by user...");
			// action depend on the current state :
			switch (m_state) {
				case audio::blockEngine::statusCreating:
					threadChangeState(audio::blockEngine::statusDie);
					break;
				case audio::blockEngine::statusStart:
					threadChangeState(audio::blockEngine::statusStop);
					break;
				case audio::blockEngine::statusRun:
					threadChangeState(audio::blockEngine::statusStop);
					break;
				case audio::blockEngine::statusStop:
					// nothing to do ...
					break;
				case audio::blockEngine::statusDie:
					// impossible state
					break;
				default:
					// Should not happen
					ABE_CRITICAL("Base: [" << m_id << "] '" << m_name << "' state failure ...");
					break;
			}
		}
		// Retrieve current action.
		switch (m_state) {
			case audio::blockEngine::statusCreating:
				ABE_DEBUG("audio::blockEngine::statusCreating");
				// change state :
				threadChangeState(audio::blockEngine::statusStart);
				break;
			case audio::blockEngine::statusStart:
				ABE_DEBUG("audio::blockEngine::statusStart");
				// call function
				autoKill = stateStart();
				// a problem occured to the function
				if (true == autoKill) {
					// error in start ==> direct end
					threadChangeState(audio::blockEngine::statusDie);
				} else {
					// change state :
					threadChangeState(audio::blockEngine::statusRun);
				}
				break;
			case audio::blockEngine::statusRun:
				ABE_DEBUG("audio::blockEngine::statusRun");
				// call function
				autoKill = stateRun();
				if (true == autoKill) {
					ABE_DEBUG("Request AutoKill");
					// error in start ==> direct end
					threadChangeState(audio::blockEngine::statusStop);
				}
				// no else
				break;
			case audio::blockEngine::statusStop:
				ABE_DEBUG("audio::blockEngine::statusStop");
				// call function
				autoKill = stateStop();
				// a problem occured to the function
				if (true == autoKill) {
					// error in stop ==> direct end
					threadChangeState(audio::blockEngine::statusDie);
				} else {
					// change state :
					threadChangeState(audio::blockEngine::statusDie);
				}
				break;
			case audio::blockEngine::statusDie:
				ABE_DEBUG("audio::blockEngine::statusDie");
				break;
			default:
				// Should not happen
				ABE_CRITICAL("Base: state failure: [" << m_id << "] name='" << m_name << "'");
				return;
		}
	}
	// exit the thread...
	ABE_INFO("Base: THEAD (END): [" << m_id << "] name='" << m_name << "'");
	return;
}



