import cv2 as cv
def face_detect_demo():
    #将图片灰度
    gray=cv.cvtColor(img,cv.COLOR_BGR2GRAY)
    #加载特征数据
    face_detector = cv.CascadeClassifier(
        'E:/soft/opencv/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml')
    faces = face_detector.detectMultiScale(gray)
    for x,y,w,h in faces:
        print(x,y,w,h)
        cv.rectangle(img,(x,y),(x+w,y+h),color=(0,0,255),thickness=2)
        cv.circle(img,center=(x+w//2,y+h//2),radius=w//2,color=(0,255,0),thickness=2)
    #显示图片
    cv.imshow('result',img)

#加载图片
img=cv.imread('face3.jpg')
#调用人脸检测方法
face_detect_demo()
cv.waitKey(0)
cv.destroyAllWindows()