#pragma once


namespace CameraUtils
{
	static float RadAngleLerp(const float current, const float target, const float alpha)
	{
		float delta = target - current;
		if (delta > PI) {
			delta -= 2*PI;
		} else if (delta < -PI) {
			delta += 2*PI;
		}
		return current + delta * alpha;
	}
	
	static FVector2d PolarLerp(const FVector2d current, const FVector2d target, const float alpha)
	{
		//special function needed because it can overflow from 3.14 to -3.14 and vice versa
		float lerpedY = CameraUtils::RadAngleLerp(current.Y, target.Y, alpha);
	
		//this is constrained already between 0.1 and 3.13, normal lerp is okay
		float lerpedX = FMath::Lerp(current.X, target.X, alpha);
	
		return FVector2D(lerpedX, lerpedY);
	}

	static float GetAngleBetweenVectorsRads(const FVector& current, const FVector& target)
	{
		return acos(FVector::DotProduct(current, target));
	}
}