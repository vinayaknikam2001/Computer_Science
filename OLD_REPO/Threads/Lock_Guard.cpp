// The lock_guard owns the mutex and it's job is to unlock it automatically when lock_guard goes out of scope..
// In lock_guard destructor it automatically unlocks the mutex.
std::mutex ml;
int buffer = 0;
void task (const char* threadNumber, int loopFor) 
{
	std::lock_guard<mutex> lock (ml);
	for(int i=0; i<loopFor; ++i) 
	{
		buffer++;
		cout << threadNumber << buffer << endl;
	}
}

int main() 
{
	thread tl(task, "TO ", 10);
	thread t2(task, "T1", 10);
	t1.join();
	t2.join();
	return 0;
}