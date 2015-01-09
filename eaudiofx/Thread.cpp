/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/debug.h>
#include <eaudiofx/Thread.h>
#include <unistd.h>

#undef __class__
#define __class__ "Thread"

static const char* threadGetCharState(enum eaudiofx::status state) {
	const char* ret = (const char*)"";
	switch (state) {
		case eaudiofx::statusNotStarted:
			ret = (const char*)"NOT_STARTED";
			break;
		case eaudiofx::statusCreating:
			ret = (const char*)"CREATING";
			break;
		case eaudiofx::statusStart:
			ret = (const char*)"START";
			break;
		case eaudiofx::statusRun:
			ret = (const char*)"RUN";
			break;
		case eaudiofx::statusStop:
			ret = (const char*)"STOP";
			break;
		case eaudiofx::statusDie:
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
void eaudiofx::Thread::threadChangeState(enum eaudiofx::status _newState) {
	int ret;
	std::unique_lock<std::mutex> lock(m_interfaceMutex);
	// debug display :
	EAUDIOFX_DEBUG("[" << m_id << "] '" << m_name << "' Change state : " << threadGetCharState(m_state) << " ==> " << threadGetCharState(_newState));
	// set the New state
	m_state = _newState;
	return;
}


eaudiofx::Thread::Thread(const std::string& _chainName) {
	if (_chainName != "") {
		m_name = _chainName;
	} else {
		m_name = "No-name";
		EAUDIOFX_WARNING("the thread has no name");
	}
	static int32_t threadIDBasic = 100;
	m_id = threadIDBasic++;
	EAUDIOFX_INFO("THREAD : Allocate [" << m_id << "] name='" << m_name << "'");
	m_state = eaudiofx::statusNotStarted;
}


eaudiofx::Thread::~Thread() {
	EAUDIOFX_INFO("THREAD : Destroy [" << m_id << "] name='" << m_name << "'");
	stop();
	m_thread->join();
	m_thread.reset();
}


int32_t eaudiofx::Thread::start() {
	int ret;
	if (eaudiofx::statusDie == m_state) {
		EAUDIOFX_INFO("Thread [" << m_id << "] name='" << m_name << "' ==> state die ... ==> delete it ...");
		stopAtEnd();
	}
	if (eaudiofx::statusNotStarted != m_state) {
		EAUDIOFX_ERROR("Failed to create [" << m_id << "] name='" << m_name << "' ==> the thread is not stopped ...");
		return eaudiofx::ERR_FAIL;
	}
	m_state = eaudiofx::statusCreating;
	m_thread = std::make_shared<std::thread>(eaudiofx::Thread::genericThreadCall, reinterpret_cast<void*>(this));
	// no else ==> the thread is started corectly... (we think)
	return eaudiofx::ERR_NONE;
}

int32_t eaudiofx::Thread::stop() {
	EAUDIOFX_INFO(" Stop [" << m_id << "] name='" << m_name << "'");
	// Set the stop flag for the thread :
	std::unique_lock<std::mutex> lock(m_interfaceMutex);
	m_flags |= 1;
	return eaudiofx::ERR_NONE;
}


int32_t eaudiofx::Thread::stopAtEnd() {
	int systemRet;
	int32_t ret = eaudiofx::ERR_NONE;

	EAUDIOFX_INFO(" Delete [" << m_id << "] name='" << m_name << "' (StopAtEnd)");
	
	// Request the thread stop:
	ret = stop();
	if (eaudiofx::ERR_NONE != ret) {
		EAUDIOFX_ERROR("The thread have a problem to stop");
		return ret;
	}
	if (eaudiofx::statusNotStarted != m_state) {
		m_thread.reset();
	}
	std::unique_lock<std::mutex> lock(m_interfaceMutex);
	m_flags = 0;
	
	m_state = eaudiofx::statusNotStarted;
	return ret;
}

// function that might be writen for every thread
bool eaudiofx::Thread::stateStart() {
	EAUDIOFX_DEBUG("Not overwrited in the herited classes: StateStart");
	// virtual function ...
	return false;
}

bool eaudiofx::Thread::stateRun() {
	EAUDIOFX_DEBUG("Not overwrited in the herited classes: StateRun");
	// virtual function ...
	usleep(100000);
	// Force the stop if this function is not overwritte
	return false;
}


bool eaudiofx::Thread::stateStop() {
	EAUDIOFX_DEBUG("Not overwrited in the herited classes: StateStop");
	// virtual function ...
	return false;
}

void eaudiofx::Thread::genericThreadCall(void* _data) {
	eaudiofx::Thread * self = reinterpret_cast<eaudiofx::Thread*>(_data);
	if (self != nullptr) {
		self->threadCall();
	} else {
		EAUDIOFX_ERROR("can not start th ethraead ...");
	}
}

void eaudiofx::Thread::threadCall() {
	bool autoKill = false;
	// Endless loop.
	while(eaudiofx::statusDie != m_state) {
		int32_t flags = 0;
		{
			std::unique_lock<std::mutex> lock(m_interfaceMutex);
			flags = m_flags;
			m_flags = 0;
		}
		if (flags == 1 ) {
			EAUDIOFX_DEBUG("Detect stop request by user...");
			// action depend on the current state :
			switch (m_state) {
				case eaudiofx::statusCreating:
					threadChangeState(eaudiofx::statusDie);
					break;
				case eaudiofx::statusStart:
					threadChangeState(eaudiofx::statusStop);
					break;
				case eaudiofx::statusRun:
					threadChangeState(eaudiofx::statusStop);
					break;
				case eaudiofx::statusStop:
					// nothing to do ...
					break;
				case eaudiofx::statusDie:
					// impossible state
					break;
				default:
					// Should not happen
					EAUDIOFX_CRITICAL("Base: [" << m_id << "] '" << m_name << "' state failure ...");
					break;
			}
		}
		// Retrieve current action.
		switch (m_state) {
			case eaudiofx::statusCreating:
				EAUDIOFX_DEBUG("eaudiofx::statusCreating");
				// change state :
				threadChangeState(eaudiofx::statusStart);
				break;
			case eaudiofx::statusStart:
				EAUDIOFX_DEBUG("eaudiofx::statusStart");
				// call function
				autoKill = stateStart();
				// a problem occured to the function
				if (true == autoKill) {
					// error in start ==> direct end
					threadChangeState(eaudiofx::statusDie);
				} else {
					// change state :
					threadChangeState(eaudiofx::statusRun);
				}
				break;
			case eaudiofx::statusRun:
				EAUDIOFX_DEBUG("eaudiofx::statusRun");
				// call function
				autoKill = stateRun();
				if (true == autoKill) {
					EAUDIOFX_DEBUG("Request AutoKill");
					// error in start ==> direct end
					threadChangeState(eaudiofx::statusStop);
				}
				// no else
				break;
			case eaudiofx::statusStop:
				EAUDIOFX_DEBUG("eaudiofx::statusStop");
				// call function
				autoKill = stateStop();
				// a problem occured to the function
				if (true == autoKill) {
					// error in stop ==> direct end
					threadChangeState(eaudiofx::statusDie);
				} else {
					// change state :
					threadChangeState(eaudiofx::statusDie);
				}
				break;
			case eaudiofx::statusDie:
				EAUDIOFX_DEBUG("eaudiofx::statusDie");
				break;
			default:
				// Should not happen
				EAUDIOFX_CRITICAL("Base: state failure: [" << m_id << "] name='" << m_name << "'");
				return;
		}
	}
	// exit the thread...
	EAUDIOFX_INFO("Base: THEAD (END): [" << m_id << "] name='" << m_name << "'");
	return;
}



