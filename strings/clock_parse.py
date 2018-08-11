import itertools

def div_check(integer, div_by):
    return int(integer)/div_by < 1

def clock_parse(S):
    result = ''
    minute = S[S.index(":"):]

    length = len(S)-1

    numbers_array = [int(d) for d in list(S.replace(":", ""))]

    counts = [0] * 10

    for i in range(0, length):
        for j in range(numbers_array[i], len(counts)):
            counts[j] +=1;

    if counts[2] == 0: return 'Not possible.'

    starts_with_two = counts[1] == 0

    if starts_with_two and counts[3] == 1: return 'Not possible.'

    numbers_available_for_minute = counts[5] - (2 if starts_with_two else 1)

    if numbers_available_for_minute == 0: return 'Not possible.'

    time = [0, 0, 0, 0]

    starts_with_two = starts_with_two or (numbers_available_for_minute >= 2 and counts[2] > counts[1])

    maxes = [2, 3, 5, 9] if starts_with_two else [1, 9, 5, 9]

    for i in range(0, len(maxes)):
        time[i] = counts.index(counts[maxes[i]])
        for j in range(time[i], len(counts)):
            counts[j] -= 1

    return str(time[0]) + str(time[1]) + ":" + str(time[2]) + str(time[3])


print(clock_parse("65:20"))
print(clock_parse("39:50"))
print(clock_parse("93:50"))
print(clock_parse("11:10"))
print(clock_parse("11:01"))
print(clock_parse("23:59"))
print(clock_parse("66:27"))
print(clock_parse("23:15"))
print(clock_parse("11:15"))
print(clock_parse("11:11"))

print(clock_parse("94:31"))
