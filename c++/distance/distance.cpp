#include<iostream>
#include<cmath>
#include"distance.h"
using namespace std;

Distance::Distance(int small, int medium, int large, char createFormat)
{
	smallMag = small;
	mediumMag = medium;
	largeMag = large;
	if(createFormat == 'I' || createFormat == 'M' || createFormat == 'N')
		format = createFormat;
	else
		format = 'I';
	setProperFormat();
	if(largeMag < 0)
	{
		smallMag = 0;
		mediumMag = 0;
		largeMag = 0;
	}
	if(largeMag == 0 && mediumMag < 0)
	{       
                smallMag = 0;
                mediumMag = 0;
                largeMag = 0;
        }
	if(largeMag == 0 && mediumMag == 0 && smallMag < 0)
	{       
                smallMag = 0;
                mediumMag = 0;
                largeMag = 0;
        }
}

Distance::Distance(double explicitDistance)
{
	double tempOne, tempTwo;
	format = 'I';
	largeMag = round(explicitDistance);
	tempOne = fmod(explicitDistance,1) * 5280;
	mediumMag = round(tempOne);
	tempTwo = fmod(tempOne,1) * 12;
	smallMag = round(tempTwo);
}

void Distance::setProperFormat()
{
	if(format == 'I')
	{
		while(smallMag >= 12)
		{
			mediumMag++;
			smallMag -= 12;
		}
		while(mediumMag >= 5280)
		{
			largeMag++;
			mediumMag -= 5280;
		}
	}
	if(format == 'M')
	{
                while(smallMag >= 100)
                {
                        mediumMag++;
                        smallMag -= 100;
                }
                while(mediumMag >= 1000)
                {
                        largeMag++;
                        mediumMag -= 1000;
                }

	}
	if(format == 'N')
	{
                while(smallMag >= 72)
                {
                        mediumMag++;
                        smallMag -= 72;
                }
                while(mediumMag >= 1013)
                {
                        largeMag++;
                        mediumMag -= 1013;
                }

	}
}

void Distance::setFormat(char newFormat)
{
	double totalDistance,tempOne, tempTwo;
	char temp = format;
	if(newFormat == 'I' || newFormat == 'M' || newFormat == 'N')
		format = newFormat;	
	else
		format = 'I';

	if(temp == 'I' && format == 'M')
	{
        	totalDistance = ((largeMag * 5280 * 12) + (mediumMag * 12) + smallMag) / 39370.079;
		largeMag = totalDistance;
        	tempOne = fmod(totalDistance,1) * 1000;
	        mediumMag = tempOne;
        	tempTwo = fmod(tempOne,1) * 100;
	        smallMag = round(tempTwo);
	}
	if(temp == 'I' && format == 'N')
	{	
		totalDistance = ((largeMag * 5280 * 12) + (mediumMag * 12) + smallMag) / 72913.386;
                largeMag = totalDistance;
                tempOne = fmod(totalDistance,1) * 1013;
                mediumMag = tempOne;
                tempTwo = fmod(tempOne,1) * 72;
                smallMag = round(tempTwo);
	}
	if(temp == 'M' && format == 'I')
        {
		totalDistance = ((largeMag * 100000) + (mediumMag * 100) + smallMag) / 160934.4;
                largeMag = totalDistance;
                tempOne = fmod(totalDistance,1) * 5280;
                mediumMag = tempOne;
                tempTwo = fmod(tempOne,1) * 12;
                smallMag = round(tempTwo);

        }
	if(temp == 'M' && format == 'N')
        {
		totalDistance = ((largeMag * 100000) + (mediumMag * 100) + smallMag) / 185200;
                largeMag = totalDistance;
                tempOne = fmod(totalDistance,1) * 1013;
                mediumMag = tempOne;
                tempTwo = fmod(tempOne,1) * 72;
                smallMag = round(tempTwo);
		
        }
	if(temp == 'N' && format == 'I')
        {
		totalDistance = ((largeMag * 1013 * 72) + (mediumMag * 72) + smallMag) / 63360;
                largeMag = totalDistance;
                tempOne = fmod(totalDistance,1) * 5280;
                mediumMag = tempOne;
                tempTwo = fmod(tempOne,1) * 12;
                smallMag = round(tempTwo);
        }
	if(temp == 'N' && format == 'M')
        {
		totalDistance = ((largeMag * 1013 * 72) + (mediumMag * 72) + smallMag) / 63360;
                largeMag = totalDistance;
                tempOne = fmod(totalDistance,1) * 1000;
                mediumMag = tempOne;
                tempTwo = fmod(tempOne,1) * 100;
                smallMag = round(tempTwo);

        }
	setProperFormat();
}

Distance Distance::add(const Distance valueAdded) const
{
	int tempSmall, tempMedium, tempLarge;
	if(format == valueAdded.format)
	{
		tempSmall = smallMag + valueAdded.smallMag;
		tempMedium = mediumMag + valueAdded.mediumMag;
		tempLarge = largeMag + valueAdded.largeMag;
		return Distance(tempSmall, tempMedium, tempLarge, format);
	}
	return Distance(smallMag, mediumMag, largeMag, format);
}

Distance Distance::subtract(const Distance valueSubed) const
{
        int tempSmall, tempMedium, tempLarge;
        if(format == valueSubed.format)
        {       
                tempSmall = smallMag - valueSubed.smallMag;
                tempMedium = mediumMag - valueSubed.mediumMag;
                tempLarge = largeMag - valueSubed.largeMag;
		Distance tempDistance(tempSmall, tempMedium, tempLarge, format);
		tempDistance.setProperFormat();
		if(tempDistance.largeMag < 0)
		{       
                	tempSmall = 0;
                	tempMedium = 0;
                	tempLarge = 0;
       		}
        	if(tempDistance.largeMag == 0 && tempDistance.mediumMag < 0)
        	{
                	tempSmall = 0;
                	tempMedium = 0;
                	tempLarge = 0;
        	}
        	if(tempDistance.largeMag == 0 && tempDistance.mediumMag == 0 && tempDistance.smallMag < 0)
        	{
                	tempSmall = 0;
                	tempMedium = 0;
                	tempLarge = 0;
        	}
                return Distance(tempSmall, tempMedium, tempLarge, format);
        }
        return Distance(smallMag, mediumMag, largeMag, format);
}

int Distance::compare(const Distance valueCompared) const
{
	if(format != valueCompared.format)
		return -2;
	if(largeMag < valueCompared.largeMag)
		return -1;
	if(largeMag > valueCompared.largeMag)
		return 1;
	if(largeMag == valueCompared.largeMag)
	{
		if(mediumMag < valueCompared.mediumMag)
        	        return -1;
	        if(mediumMag > valueCompared.mediumMag)
                	return 1;
		if(mediumMag == valueCompared.mediumMag)
		{
			if(smallMag < valueCompared.smallMag)
        	                return -1;
                	if(smallMag > valueCompared.smallMag)
                        	return 1;
                	if(smallMag == valueCompared.smallMag)
				return 0;
		}
	}
}

Distance Distance::operator+(const Distance &valueAdded) const
{
	Distance result(0);
	if(format == valueAdded.format)
	{
		result.smallMag = smallMag + valueAdded.smallMag;
		result.mediumMag = mediumMag + valueAdded.mediumMag;
		result.largeMag = largeMag + valueAdded.largeMag;
		result.format = format;
		result.setProperFormat();
		return result;
	}
	else
	{	
		result.smallMag = smallMag;
		result.mediumMag = mediumMag;
		result.largeMag = largeMag;
		result.format = format;
		return result;
	}
}

Distance Distance::operator-(const Distance &valueSubed) const
{
        Distance result(0);
        if(format == valueSubed.format)
        {
                result.smallMag = smallMag - valueSubed.smallMag;
                result.mediumMag = mediumMag - valueSubed.mediumMag;
                result.largeMag = largeMag - valueSubed.largeMag;
                result.format = format;
		result.setProperFormat();
                if(result.largeMag < 0)
                {
                        result.smallMag = 0;
                        result.mediumMag = 0;
                        result.largeMag = 0;
                }
                if(result.largeMag == 0 && result.mediumMag < 0)
                {
                        result.smallMag = 0;
                        result.mediumMag = 0;
                        result.largeMag = 0;

                }
                if(result.largeMag == 0 && result.mediumMag == 0 && result.smallMag < 0)
                {
                        result.smallMag = 0;
                        result.mediumMag = 0;
                        result.largeMag = 0;

                }
                return result;
        }
        else
        {
		result.smallMag = smallMag;
                result.mediumMag = mediumMag;
                result.largeMag = largeMag;
                result.format = format;
                return result;
	}
}

bool operator==(const Distance &valueOne,const Distance &valueTwo)
{
	Distance temp = valueTwo;
	if(valueOne.format != valueTwo.format)
		temp.setFormat(temp.format);
	if(valueOne.smallMag == temp.smallMag
	&& valueOne.mediumMag == temp.mediumMag
	&& valueOne.largeMag == temp.largeMag)
		return true;
	return false;
}

bool operator<=(const Distance &valueOne,const Distance &valueTwo)
{       
	Distance temp = valueTwo;
        if(valueOne.format != valueTwo.format)
                temp.setFormat(valueOne.format);
	if(valueOne.largeMag < temp.largeMag)
		return true;
	if(valueOne.largeMag == temp.largeMag)
	{
		if(valueOne.mediumMag < temp.mediumMag)
			return true;
		if(valueOne.mediumMag == temp.mediumMag)
		{
			if(valueOne.smallMag < temp.smallMag)
				return true;
			if(valueOne.smallMag == temp.smallMag)
				return true;
		}
	}
        return false;
}

bool operator>=(const Distance &valueOne,const Distance &valueTwo)
{
	Distance temp = valueTwo;
        if(valueOne.format != valueTwo.format)
                temp.setFormat(valueOne.format);
        if(valueOne.largeMag > temp.largeMag)
                return true;
        if(valueOne.largeMag == temp.largeMag)
        {
                if(valueOne.mediumMag > temp.mediumMag)
                        return true;
                if(valueOne.mediumMag == temp.mediumMag)
                {
                        if(valueOne.smallMag > temp.smallMag)
                                return true;
                        if(valueOne.smallMag == temp.smallMag)
                                return true;
                }
        }
        return false;
}

bool operator<(const Distance &valueOne, const Distance &valueTwo)
{	
	Distance temp = valueTwo;
        if(valueOne.format != valueTwo.format)
                temp.setFormat(valueOne.format);
        if(valueOne.largeMag < temp.largeMag)
                return true;
        if(valueOne.largeMag == temp.largeMag)
        {
                if(valueOne.mediumMag < temp.mediumMag)
                        return true;
                if(valueOne.mediumMag == temp.mediumMag)
                {
                        if(valueOne.smallMag < temp.smallMag)
                                return true;
                }
        }
        return false;
}

bool operator>(const Distance &valueOne, const Distance &valueTwo)
{
	Distance temp = valueTwo;
        if(valueOne.format != valueTwo.format)
                temp.setFormat(valueOne.format);
        if(valueOne.largeMag > temp.largeMag)
                return true;
        if(valueOne.largeMag == temp.largeMag)
        {
                if(valueOne.mediumMag > temp.mediumMag)
                        return true;
                if(valueOne.mediumMag == temp.mediumMag)
                {
                        if(valueOne.smallMag > temp.smallMag)
                                return true;
                }
        }
        return false;
}

bool operator!=(const Distance &valueOne, const Distance &valueTwo)
{
	Distance temp = valueTwo;
        if(valueOne.format != valueTwo.format)
                temp.setFormat(valueOne.format);
        if(valueOne.smallMag != temp.smallMag
        || valueOne.mediumMag != temp.mediumMag
        || valueOne.largeMag != temp.largeMag)
                return true;
        return false;
}

ostream& operator<<(ostream &out, const Distance &distanceObj)
{
	if(distanceObj.format == 'I')
	{
		out << "The distance is " << distanceObj.largeMag << " miles, " << distanceObj.mediumMag << " feet and " << distanceObj.smallMag << " inches" << endl;
		return out;
	}
	if(distanceObj.format == 'N')
	{
		out << "The distance is " << distanceObj.largeMag << " nautical  miles, " << distanceObj.mediumMag << " fathoms and " << distanceObj.smallMag << " inches" << endl;
		return out;
	}
        
	if(distanceObj.format == 'M')
	{
		out << "The distance is " << distanceObj.largeMag << " kilometers, " << distanceObj.mediumMag << " meters and " << distanceObj.smallMag << " centimeters" << endl;
		return out;
	}
        

}
istream& operator>>(istream &in,Distance &distanceObj)
{
	char ignoreComma;
	in >> distanceObj.largeMag;
	in >> ignoreComma; 
	in >> distanceObj.mediumMag;
	in >> ignoreComma; 
	in >> distanceObj.smallMag;
	in >> distanceObj.format;
	return in;
}
