# 在一个旋转数组中找最小值(牛客网-剑指offer)
# [1,2,3,4,5] 的旋转数组 [4,5,1,2,3] 的最小值为1

def find_min(arr):
    result = arr[0]
    for i in range(0, len(arr)-1):
        if arr[i] > arr[i+1]:
            return arr[i+1]
    return result

if __name__ == '__main__':
    print(find_min([4,5,1,1,3]))
