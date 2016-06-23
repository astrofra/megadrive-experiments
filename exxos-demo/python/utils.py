import math


def RangeAdjust(val, in_lower, in_upper, out_lower, out_upper):
    return (val - in_lower) / (in_upper - in_lower) * (out_upper - out_lower) + out_lower


def Clamp(x, in_lower, in_upper):
	return min((max(x, in_lower)), in_upper)


def mapValueToArray(val, in_lower, in_upper, mapping_array):
	val = RangeAdjust(val, in_lower, in_upper, 0.0, 1.0)
	val = Clamp(val, 0.0, 1.0)
	array_pos = val * (len(mapping_array) - 1)
	ceil_pos = math.ceil(array_pos)
	floor_pos = math.floor(array_pos)
	return mapping_array[floor_pos] * float(ceil_pos - array_pos) + mapping_array[ceil_pos] * (1.0 - (float(ceil_pos - array_pos)))

def EaseInOutQuick(x):
	x = Clamp(x, 0.0, 1.0)
	return (x * x * (3 - 2 * x))


def EaseInOutByPow(x, p=2.0):
	x = Clamp(x, 0.0, 1.0)
	y = math.pow(x, p) / (math.pow(x, p) + math.pow(1 - x, p))
	return y