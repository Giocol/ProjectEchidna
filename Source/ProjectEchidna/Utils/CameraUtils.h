#pragma once


namespace CameraUtils
{
	static float RadAngleLerp(float current, float target, float alpha)
	{
		float delta = target - current;
		if (delta > PI) {
			delta -= 2*PI;
		} else if (delta < -PI) {
			delta += 2*PI;
		}
		return current + delta * alpha;
	}
	
	static FVector2d PolarLerp(FVector2d current, FVector2d target, float alpha)
	{
		//special function needed because it can overflow from 3.14 to -3.14 and vice versa
		float lerpedY = CameraUtils::RadAngleLerp(current.Y, target.Y, alpha);
	
		//this is constrained already between 0.1 and 3.13, normal lerp is okay
		float lerpedX = FMath::Lerp(current.X, target.X, alpha);
	
		return FVector2D(lerpedX, lerpedY);
	}

	static float GetAngleBetweenVectorsRads(FVector current, FVector target)
	{
		return acos(FVector::DotProduct(current, target));
	}
}