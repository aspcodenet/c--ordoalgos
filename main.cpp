#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>



enum class SensorType
{
	Altitude,
	SpeedInKmh,
	FuelConsumption
};

class SensorData
{
	float value;
	SensorType sensorType;
	time_t time;
public:
	SensorType GetSensorType() { return sensorType; }
	float GetValue() { return value; }
	void SetValue(float v) { value = v; }
	time_t GetTime() { return time; }
	SensorData(SensorType sensorType, float value, time_t time)
	{
		this->value = value;
		this->sensorType = sensorType;
		this->time = time;
	}
};
void FillData(std::vector<SensorData> &v);
time_t CreateTime(int year, int month, int day, int hour, int minute, int second);


// vector<HockeyStat> points
// points[0] = leder 
// points[1] = ligger tvåa
// points[9] = ligger tia
// Vilken plats ligger Mikko Rantanen på?

// ordo O(1) - HELIGA GRAALEN Ordo
SensorData &getData(std::vector<SensorData> &v, int index){
    //sleep(1000000000000);
    return v[index];  // index 0 eller index  10000000
}


// ordo O(n)  // om vi slänger in dubbelt så många poster -> "dubbelt" så lång tid
bool exists(const std::vector<SensorData> &v, float value){
    for(auto sensorData : v){
        if(sensorData.GetValue() == value){
            return true;
        }
    }
    return false;
}

// ordo O(n)  // om vi slänger in dubbelt så många poster -> "dubbelt" så lång tid
bool stupidExists(const std::vector<SensorData> &v, float value){
    bool found = false;
    for(auto sensorData : v){
        if(sensorData.GetValue() == value){
            found = true;
        }
    }
    return found;
}




const bool duplicateValues(std::vector<SensorData> &v, float value){
    for(int thisIndex = 0; thisIndex < v.size();thisIndex++){
        for(int compareIndex = thisIndex+1; compareIndex < v.size();compareIndex++){
            if(v[thisIndex].GetValue() == v[compareIndex].GetValue()){
                return true;
            }
        }
    }
    return false;
}



int main(){
    std::vector<SensorData> sensorData;
	FillData(sensorData);
    return 0;
}



void FillData(std::vector<SensorData>& v)
{
	srand(time(NULL));

	time_t tid = CreateTime(2012, 1, 1, 1, 1, 1 );
	for (int i = 0; i < 100000; i++)
	{
		SensorType type = static_cast<SensorType>(rand() % 3);
		float value = 0.0f;
		if (type == SensorType::Altitude)
			value = rand() % 1000;
		else if (type == SensorType::FuelConsumption)
			value = rand() * 3.0f;
		else if (type == SensorType::SpeedInKmh)
			value = rand() % 110;
		else
		{
			value = 99;
		}
		v.push_back(SensorData(type,value,tid));
		tid = tid + rand() % 10 + 1;
	}
}


time_t CreateTime(int year, int month, int day, int hour, int minute, int second)
{
	struct tm tid = { 0 };
	tid.tm_year = year-1900;
	tid.tm_mon = month - 1;
	tid.tm_mday = day;
	tid.tm_hour = hour;
	tid.tm_min = minute;
	tid.tm_sec = second;
	return mktime(&tid);
}