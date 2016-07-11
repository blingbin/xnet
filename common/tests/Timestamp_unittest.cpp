#include <vector>
#include <stdio.h>
#include "Timestamp.h"

using xnet::Timestamp;

void passByConstReference(const Timestamp& x)
{
	printf("%s\n", x.toString().c_str());
}

void passByValue(Timestamp x)
{
	printf("%s\n", x.toString().c_str());
}

void benchmark()
{
	const int kNumber = 1000 * 1000;

	std::vector<Timestamp> notes;
	notes.reserve(kNumber);
	for (int i = 0; i < kNumber; ++i)
	{
		notes.push_back(Timestamp::now());
	}
	printf("%s\n", notes.front().toString().c_str());
	printf("%s\n", notes.back().toString().c_str());
	printf("%f\n", timeDifference(notes.back(), notes.front()));

	int increments[100] =
	{ 0 };
	int64_t start = notes.front().microSeconds();
	for (int i = 1; i < kNumber; ++i)
	{
		int64_t next = notes[i].microSeconds();
		int64_t inc = next - start;
		start = next;
		if (inc < 0)
		{
			printf("reverse!\n");
		}
		else if (inc < 100)
		{
			++increments[inc];
		}
		else
		{
			printf("big gap %d\n", static_cast<int>(inc));
		}
	}

	for (int i = 0; i < 100; ++i)
	{
		printf("%2d: %d\n", i, increments[i]);
	}
}

int main()
{
	Timestamp now(Timestamp::now());
	printf("%s\n", now.toString().c_str());
	passByValue(now);
	passByConstReference(now);

	Timestamp invalid(Timestamp::invalid());
	printf("\ninvalid.microSecondsSinceEpoch=%ld\n\n", invalid.microSecondsSinceEpoch());
	benchmark();
}

