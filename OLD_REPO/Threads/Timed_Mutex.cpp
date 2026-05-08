//Example for Timed Mutex try_lock_for(); This function accepts time in seconds and return true or false.
int myAmount = 0;
std::timed_mutex m;

void increment (int i) 
{
	//If mutex is not locked then 1st thread will lock the mutex.
	//Second thread will wait for specified time (2seconds) here if thread still not get mutex.
	// It will go in else condition.. and print msg couldn't enter.
	if(m.try_lock_for(std::chrono::seconds(2)))
	{
		++myAmount;
		std::this thread::sleep_for(std::chrono::seconds(1));
		cout << "Thread " << i <<"Entered" << endl;
		m.unlock();
	}
	else
	{
		cout << "Thread " << i << "Couldn't Enter" << endl;
	}
}

int main() 
{
	std::thread t1(increment, 1);
	std::thread t2(increment, 2);
	t1.join();
	t2.join();
	cout << myAmount << endl;
	return 0;
}

//Example for Timed Mutex try_lock_until();
void increment (int i) 
{
	auto now = std::chrono::steady_clock::now(); //Will allow this thread from this stat
	if(m.try_lock_until (now + std::chrono::seconds (1)))
	{
		++my Amount;
		std::this thread::sleep_for (std::chrono::seconds ());
		cout << "Thread " << i <<"Entered" << endl;
		m.unlock();
	}
	else
	{
		cout << "Thread " << i << "Couldn't Enter" << endl;
	}
}