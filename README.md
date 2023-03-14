

졸업논문으로 2016년에 제작된 컴퓨터 비전 프로젝트입니다. 두 이미지의 관계인 '호모그래피'라는 것을 통해 유저의 위치와 자세를 획득하는 것을 목표로 하였습니다. 학부 재학 당시 컴퓨터 비전에 관심이 있던 저를 포함한 3명의 학생이 제작하였고 걸린 기간은 3개월입니다. 아래는 프로젝트의 이해를 돕기 위한 설명입니다. 

- 호모그래피라는 것을 이용하여 유저의 1)위치와 2)자세를 획득한다. 위치는 r,theta,phi이며 자세는 roll, tilt, pan이다.
- open CV 라이브러리를 사용하려고 했으나 우리가 원하는 성분은 내부 행렬이라 사용하지 못했다.
- 임의의 두 이미지의 관계를 얻기 위해 RGB, Yellow 색 4개의 점을 이용하였다.
- 내부 행렬 데이터를 알아내기 위해 '소실선'이라는 개념을 적용하였다.
- 실험을 통하여 두 이미지 사이의 관계 데이터를 직접 구하였다.



## Homography

<img src="https://velog.velcdn.com/images/iankimdev/post/ea6d7fb3-a96e-418f-bbe3-08901e5c56c2/image.png" width="50%" height="50%">
두 평면사이의 Perspective Transform(원근 변환, 투시 변환) 관계이다. 카메라로부터 실제로 얼마나 멀리 떨어져 있고 또 키는 얼마나 큰지 알아내는 것은 영상기하학의 가장 빈번한 응용 중 하나이다. 영상내 임의의 영상좌표(픽셀좌표)에 대해 대응되는 2D 지면좌표(ground plane coordinate)를 구하는 문제로 귀결되며 임의의 네 대응쌍을 이용해서 구한 Homograpy를 다른 모든 점들에 대해서도 동일하게 적용할 수 있다



#### Homography matrix
<br>
<img src="https://velog.velcdn.com/images/ian-k-developer/post/631e71f7-402c-404d-85b9-238d40bb6161/image.png" width="50%" height="50%">



> 기준점을 4개로 잡은 이유
`h33` 은 1로 일정하며, `w` 는 scale factor로, `h31`과 `h32`의 합으로 표현되는 변수이다.
8개의 `h`를 알아내야 하므 로 **4쌍의 대응점**이 필요하다. 이를 연립방정식을 통하여 얻어낼 수 있다.


`h31`과 `h32`는 변환된 후의 평면의 기울어진 방향과 기울어진 정도를 알아낼 수 있는 벡터이다.
`h13`과 `h23`은 평행 이동한 벡터를 나타낸다.
`h11`, `h12`, `h21`, `h22`는 평행이동, 팽창 수축, 회전, 평면의 기울어짐 등이 종합적으로 반영되어
있다.
<br><br>


식을 풀면,

<img src="https://velog.velcdn.com/images/ian-k-developer/post/d6aa0a60-3397-4b27-9433-00b7cdf07e32/image.png" width="50%" height="50%" align="left"><br>


<br><br><br><br><br><br><br><br><br><br>

x, y에 대한 식으로 표현하면,

<img src="https://velog.velcdn.com/images/ian-k-developer/post/f31e8ab8-e74f-4763-8d8c-62b670bd5199/image.png" width="70%" height="50%" align="left">
<br><br><br><br><br>

이를 행렬로 표현하면,

<img src="https://velog.velcdn.com/images/ian-k-developer/post/91d3fbf8-efd0-4f9f-9df6-149d45983424/image.png" width="50%" height="50%" align="left">

<br><br><br><br><br><br><br><br><br><br><br><br>





이며, 역행렬을 통해 H를 구한다.
<img src="https://velog.velcdn.com/images/ian-k-developer/post/00ed65bf-c673-485d-ae2e-0a62b24108a8/image.png" width="20%" height="30%" align="left">

<br><br><br><br><br><br><br>




## 소실선

물리공간에서 평행한 모든 직선들은 영상에서 모두 동일한 소실점을 갖는다. 동일 평면에 속한 직선들의 소실점들은 모두 일직선상에 존재하게 되는데 이 선을 소실선이라고 한다

<img src="https://velog.velcdn.com/images/ian-k-developer/post/478a540b-af56-4d2a-8c0d-97956a7c54c4/image.jpeg" width="23%" height="30%" align="left">

<img src="https://velog.velcdn.com/images/ian-k-developer/post/83e401e7-b5a6-4564-a634-2adb9455f3d5/image.png" width="30%" height="30%" align="left">

<br><br><br><br><br><br><br><br>



<img src="https://velog.velcdn.com/images/ian-k-developer/post/6828b1f6-b788-4140-a8bf-bc7639da70f6/image.png" width="30%" height="30%" align="left">

<br><br>
기하학적으로 봤을 때, 어떤 평면에 대한 소실선(vanishing line)은 이 평면과 수평이고 카메라 원점을 지나는 평면이 이미지 평면과 만나서 생기는 교선이다.

소실점(vanishing point)도 마찬가지이다. 지면 위의 한 직선을 이미지에 투영해 보면 직선을 무한히 확장하였을 경우 결국 소실선(L) 상의 어느 한 점으로 수렴하게 됨을 쉽게 상상할 수 있다.
<br><br>

두 개 이상의 소실점을 통해 소실선을 구할 수 있다. 위에서 언급했듯이 소실선은 서로 다른 두 개 이상의 소실점을 통해 구할 수 있는데 오차를 줄이기 위해 여러 개의 소실점을 통해 구하기로 한다. 호모그래피 행렬의 내부의 값을 통해서 다수의 소실점을 구할 수 있다.

소실 점이란 무한히 긴 직선이 기울어져 있어서 나타나는 수렴하는 점이다. 이와 같은 특성을 이용 해서 x, y 값을 어떤 직선을 따라 무한히 증가(혹은 감소) 시킬 때 x’, y’ 값이 수렴한다면 이것이 소실점이 될 것이며, 직선을 평행하지 않은 다른 직선으로 바꾸어서 x,y 값을 증가시키면 다른 소실점이 나올 수 있다.

소실선을 이용하여 현재 자세를 구할 수 있다. 수평선과 비슷한(지구는 둥글기 때문에 완전 같지는 않다.) 특징을 가지고 있어서 내가 바닥과 수평 방향을 바라보고 있다면 **내 시야에 중심에 소실선이 정확하게 일치**하게 되며 소실선이 내 시야중심보다 아래 있으면 내가 위를 바라보고 있는 것이고 반대로 위에 있으면 내가 아래를 바라보는 것이므로 **내가 어느 각도로 바라보고 있는지 소실선을 통해 알 수 있다**. 

<img src="https://velog.velcdn.com/images/ian-k-developer/post/a9314811-75a3-42bb-aace-7ca0f2e85652/image.png" width="30%" height="30%" align="left">

<img src="https://velog.velcdn.com/images/ian-k-developer/post/7bd0664a-6b0c-4e76-a468-2b359c51931c/image.png" width="30%" height="30%" align="left">
<br><br><br><br><br><br><br><br>
소실선의 위치를 알면 캘리브레이션을 하지 않고도 카메라의 팬(pan), 틸트(tilt), 롤(roll)을 알아낼 수 있다.

<br><br>


## 카메라와 소실선을 이용한 유저의 자세 (roll, tilt, pan)
<img src="https://velog.velcdn.com/images/iankimdev/post/0a95d791-4164-4cd0-a31e-e16cb1daf3aa/image.png" width="50%" height="30%" align="left">
<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>
사진에서 자세를 기술하는 용어중에 카메라의 팬(pan), 틸트(tilt), 롤(roll) 개념이 있다. Tilt는 위, 아래를 바라보는 것이고, Roll은 갸우뚱하게 바라보는 것이고, Pan은 좌, 우로 바라보는 것이다. 이 개념으로 사용자의 자세를 기술 할 수 있다.
<br><br><br><br><br>

#### 소실선과 롤(roll)
소실선을 이용해서 롤을 구하는 것은 비교적 간단하다. 카메라가 롤 방향으로 회전하면 영상에서 소실선 또한 롤(roll) 각도만큼 기울어진다. 따라서 소실선의 기울어진 각을 측정하면 카메라의 롤(roll)이 구해진다.

<img src="https://velog.velcdn.com/images/ian-k-developer/post/c734b207-7e76-48dc-89a3-9c7ff83f0c69/image.jpeg" width="30%" height="30%" align="left">
<img src="https://velog.velcdn.com/images/ian-k-developer/post/5be59f89-6540-400e-b722-11b55be31074/image.png" width="25%" height="30%" align="left">
<br><br><br><br><br><br><br><br>



```
x : 픽셀의 x좌표
y : 픽셀의 y좌표
fx : x축 방향 카메라 초점거리.
fy : y축 방향 카메라 초점거리.
```
<br><br>

#### 소실선과 틸트(tilt)
소실점의 y 좌표를 알면 카메라의 틸트(tilt)는 간단하게 계산된다. 
소실점(vanishing point)의 재미있는 성질은 카메라의 틸트(tilt)가 0일 때는 주점과 동일 수평선 상에 생성되고 틸트가 +일 경우에는 주점의 아래쪽에, 틸트가 -일 경우에는 주점의 위쪽에 소실점이 형성된다는 점이다.


<img src="https://velog.velcdn.com/images/ian-k-developer/post/e4296165-4bfe-43c0-8583-99c43b7021f2/image.png" width="30%" height="30%" align="left">
<img src="https://velog.velcdn.com/images/ian-k-developer/post/cdd3a335-f0af-45d3-9eae-5dfac1c41514/image.png" width="20%" height="30%" align="left">
<br><br><br><br><br><br><br><br>

하지만, roll 회전이 존재하는 경우에는 소실점만으로는 문제 해결이 안되며 소실선(vanishing line) 정보가 필요하다. 소실선이 주어질 경우, 카메라 주점과 소실선의 수직거리를 d(픽셀 단위), 초점거리를 f라 하면 틸트는 θtilt = atan2(d, f)로 계산


```
vy : 소실점의 y좌표(픽셀좌표), 
cy : 주점의 y좌표, (주점 cx, cy는 카메라 렌즈의 중심 즉, 핀홀에서 이미지 센서에 내린 수선의 발의 영상좌표(단위는 픽셀)로서 일반적으로 말하는 영상 중심점)
fy : y축 방향 카메라 초점거리.
```





<br><br>
#### 소실선과 팬(pan)
카메라의 팬(pan)은 틸트(tilt)나 롤(roll)과는 달리 절대적인 기준(원점)을 잡기가 애매하다. 따라서 여기서는 이미지 상의 물체(직선)와 실제 카메라 광학축 방향과의 상대적인 pan각을 구하는 문제로 접근한다 (top-view를 기준으로 했을 때의 사잇각).

<img src="https://velog.velcdn.com/images/ian-k-developer/post/fd26f19c-0678-458c-ba50-0a2b802aeda1/image.png" width="40%" height="30%" align="left">
<img src="https://velog.velcdn.com/images/ian-k-developer/post/d245f7c0-dec6-47a7-96fe-34281c965271/image.png" width="25%" height="30%" align="left">
<br><br><br>
<img src="https://velog.velcdn.com/images/ian-k-developer/post/8821cc0f-7e67-4836-bcaf-b8d6697204a5/image.png" width="33%" height="30%" align="left">
<br><br><br><br><br>

```
C : 카메라의 원점
P : 이미지의 주점 (주점 cx, cy는 카메라 렌즈의 중심 즉, 핀홀에서 이미지 센서에 내린 수선의 발의 영상좌표(단위는 픽셀)로서 일반적으로 말하는 영상 중심점)
V : 소실점
f : 초점거리
H : 주점에서 소실선에 내린 수선의 발
d : 수직거리
```

<br><br>

  
## 유저의 위치 (r, theat, phi)



<img src="https://velog.velcdn.com/images/iankimdev/post/7414ffe0-5f61-4206-a0c9-495b9527a4b7/image.png" width="40%" height="30%" align="left">



#### 유저 자세와 픽셀값을 통한 위치 구하기

위치는 카메라 상의 이미지 중심과 실제 이미지의 중심이 일치할 때에 알 수 있다. 이 경우에는 유저의 자세(카메라)가 바로 유저의 위치를 결정지을 수 있게 되는데 그 이유는 실제 이미지에서 카메라로 이은 가상의 선과 카메라 이미지의 중심(유저의 시야 중심)을 따라 이은 선이 일치하기 때문이다. 여기서 힌트를 얻어서 현재의 자세 정보에다가 실제 이미지 중심과 카메라 시야 중심과의 차이 벡터를 통하여 사용자의 위치를 얻을 수 있다고 생각하게 되었으며 이것을 기반으로 프로그램을 구현하고 있다.



<br><br><br><br><br><br><br><br><br>



#### RGBY 평면과 카메라와의 거리 계산

어떤 한 선분의 길이는 거리와 반비례 관계로 나타난다. 하지만 이것을 이용하기 위해선 시야의 각도가 변하지 않는다는 조건이 필요하다. 이미지의 기준점이 사진으로 찍혔을 때 왜곡된 이미지로 표현되었을 때 기준점(원)이 찌그러져서 타원 모양이 될 텐데 이 타원에서 가장 긴 지름이 바로 위에서 말한 각도가 유지된 체 거리만 바뀐 선분이다. 이 지름은 각도가 변해도 거리가 같다면 변하지 않는다.


<img src="https://velog.velcdn.com/images/ian-k-developer/post/92c4c9aa-98c7-4f76-ae25-f3b3caa55e68/image.png" width="43%" height="30%" align="left">
<br><br><br><br><br><br><br><br><br>
왜냐하면 위의 두 그림과 같이 기울어진 방향으로는 원이 압축되지만 기울어지지 않은 방향으로는 그 길이가 유지 되기 때문이다. **타원의 긴 지름은 기울어짐으로 인한 선분의 길이 감소가 일어나지 않으므로 이것을 기준으로 코드와 나와의 거리를 측정하는데 사용하기에 적합**하다.


다만 이 방법은 원 위의 점의 갯수만큼 호모그래피 변환을 실시해야 하며 지름을 찾기 위해 가장 거리가 먼 두 점을 찾는 등 연산량이 많아서 프로그램을 느리게 할 가능성이 있다. 그래서 **타원의 가장 긴 지름이 소실선으로 향하는 가장 짧은 벡터와 항상 수직하다는 점을 이용**하여 타원의 긴 지름을 쉽게 구하도록 하였다.



## 설계
#### 기준 이미지
: RGB와 Yellow 색의 4개의 기준점을 가진 평면
<img src="https://velog.velcdn.com/images/ian-k-developer/post/69ed8c5d-1ab9-466c-ba1c-d2c672f5173a/image.png" width="23%" height="30%" align="left">




<br><br><br><br><br><br><br><br><br><br><br>


#### 이미지의 소실선 벡터
그림판을 통해 픽셀의 좌표를 알 수 있다. 호모그래피 프로그램에 기준이되는 이미지의 RGBY 네점의 좌표를 넣어 이미지의 중앙점을 (0,0)으로 맞춘 후 호모그래피 행렬을 통해 세 개의 소실점을 통해 무조건 나오는 2개의 소실점을 찾은 후 소실선 벡터를 구한다. 


> 소실점을 구하는 세가지 방법 
	1. x를 무한으로 보내고 y는 0에 둔다. (x=∞, y=0)
	2. x는 0에 두고 y를 무한으로 보낸다.(x=0, y=∞) 
	3. x,y 둘 다 무한으로 보낸다. (x=∞, y=∞) 


<br>

#### 호모그래피 행렬 계산을 통한 소실선벡터 도출
<img src="https://velog.velcdn.com/images/iankimdev/post/cda2ba2c-1274-4c41-97f1-dc71a11f2f3f/image.png" width="50%" height="30%" align="left">

<br><br><br><br><br><br><br><br><br><br><br><br><br>

유저가 카메라로 찍는 이미지의 RGB, Yellow 점의 좌표를 넣어주고 호모그래피 행렬을 통해 소실선 벡터를 구해준다.
기준 이미지와, 실제 사진 이미지의 소실선 벡터 두 개를 구해준다.

![](https://velog.velcdn.com/images/ian-k-developer/post/b53255f8-0a7f-46fd-9284-01b01a1e5a89/image.png)

![](https://velog.velcdn.com/images/iankimdev/post/4ef80802-b7e1-4598-831d-f509e82ba032/image.png)


#### 유저의 자세 도출

<img src="https://velog.velcdn.com/images/ian-k-developer/post/f3a18599-cc69-4165-9cda-99581688380e/image.png" width="40%" height="30%" align="left">

<img src="https://velog.velcdn.com/images/ian-k-developer/post/4408e602-bf6c-4ac2-afe3-ccc70b694fe0/image.png" width="43%" height="30%" align="left">
<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>

```
QR코드 : 실제 이미지
시야중심 : 카메라 시야(유저 시야)중심
```

roll : 두 소실선의 각도 차이

미리 실험을 통해 얻어놓은 `각도에 따른 픽셀좌표`와 `픽셀수 샘플`과 비교를 하여 두개의 소실선의 각도 차이를 얻어낸다.
각도 당 픽셀은 실험을 통해 구하였다고 글 아래에 실험 방법과 값을 올려두었다. 
> 387 pixel / 5 degree

tilt : 두 소실선의 y성분 픽셀 좌표 차이를 통해 픽셀 수로 각도를 도출한다. <br>
pan : 기준이미지의 중심으로 가는 벡터와 사진이미지(호모그래피 변환된)의 중심으로 가는 각도 차이다.
설계한 프로그램 상 code to vanishing line과 zero to vanishing line의 각도 차이다.


#### 이미지와 카메라의 거리 도출

호모그래피를 이용하여 해당하는 점들을 변환된 코드 좌표공간으로 이동시킨다. 이렇게 하면 원이 찌그러져서 타원이 될 텐데 이 타원에서 가장 긴 지름이 바로 위에서 말한 각도가 유지된 체 거리만 바뀐 선분이다. 타원의 긴 지름은 기울어짐으로 인한 선분의 길이 감소가 일어나지 않으므로 이것을 기준으로 코드와 나와의 거리를 측정하는데 사용

> 기준점의 지름, 호모그래피로 변환된(실제이미지)의 기준점의 지름
이 두 지름의 관계를 이용하여 r(실제 이미지와 카메라와의 거리)을 구할 수 있다.

r : 픽셀좌표를 통해 두 지름의 길이를 알고 있으며 `두 지름의 관계에 대한 거리`를 실험을 통해 미리 알고 있으므로 r을 구할 수 있다.

theta : 두 소실선의 y성분 픽셀 좌표 차이를 통해 픽셀 수로 각도를 도출한다. 

phi : 기준이미지의 중심으로 가는 벡터와 사진이미지(호모그래피 변환된)의 중심으로 가는 각도 차이를 픽셀 수로 알 수 있다.


## Trouble Shooting 및 실험 데이터
설계 시 발생했던 문제점과 해결 방안 요약

1) 호모그래피를 구할때 opencv의 함수로 구하려고 했으나 호모그래피 내부 변수를 빼낼 수가 없었다.
-> 직접 호모그래피를 구하는 함수를 만들어서 그 변수값을 구함

2) 소실선을 구하여 소실선과 화면 중심간에 픽셀 거리를 알았다고 하더라도 픽셀간격과 실제 각도와의 관계를 모른다.
-> 실험을 통해 Data를 얻는다.



<br>

### 각도 당 픽셀 수 실험

각도에 따른 픽셀 샘플수를 얻기위해 사진을 찍어 픽셀을 계산한다.

<img src="https://velog.velcdn.com/images/ian-k-developer/post/2c19c628-1d95-4a1f-8766-bcc78c71586e/image.png" width="49%" height="30%" align="left">

<img src="https://user-images.githubusercontent.com/120093816/218250026-9bb79198-0865-41ff-9d3c-4f5ba1404929.png" width="45%" height="30%" align="left">


<br><br><br><br><br><br><br><br><br><br><br><br><br><br>

픽셀 값을 측정하기 위해 렌즈의 시야각에 맞게 선을 그은 후 10도 단위로 선을 그었다. 카메라의 위치를 조정하여 일자로 보이게 셋팅한 후 촬영하였다. -30 도에서 30 도까지 5 도 간격으로 측정한 픽셀 수이다. -15 도에서 15 도까지 평균값인 387 을 기준 상수로 사용할 것이고 관계식은 tan 함수를 사용한다. 픽셀 간의 각도를 알기 위해 387pixel / 5degree을 사용하기로 했는데 기울 기에 따른 거리보상을 위해 387로 통일 하지 않고, tan()값으로 각도에 따른 픽셀 값을 구한다.


<br><br>



### roll, tilt, pan, r, phi, theta 데이터 구축

tilt 실험

- 평면을 5도 간격으로 측정하여 샘플을 얻는다.
- 호모그래피 프로그램에 평면의 RGB ,Yellow 점의 좌표 삽입 
- 소실선 벡터 얻은 후 시야중심과 소실선의 각 Θ 도출


<img src="https://velog.velcdn.com/images/ian-k-developer/post/e6d0a72d-fd3f-48ca-ad35-bed4733ba638/image.png" width="45%" height="30%" align="left">

<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>
pan 실험

- 평면의 회전을 10도마다 측정하여 샘플을 얻는다.
- 호모그래피 프로그램에 평면의 RGB ,Yellow 점의 좌표 삽입 
- 소실선 벡터 얻은 후 시야중심과 소실선의 각 π 도출


<img src="https://velog.velcdn.com/images/ian-k-developer/post/6a9f3f10-274e-41aa-8274-5b956fb53588/image.png" width="45%" height="30%" align="left">

<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>

theta 실험
<img width="955" alt="Screen Shot 2023-02-06 at 7 23 50 PM" src="https://user-images.githubusercontent.com/120093816/216947330-159ae8f0-6a7e-4ac6-80fb-c94653c0dd0e.png">

r 실험
![Screen Shot 2023-02-06 at 7 24 18 PM](https://user-images.githubusercontent.com/120093816/216947429-c1de25dd-2200-44d7-b6b4-0810b67f09f4.png)

phi 실험
![Screen Shot 2023-02-06 at 7 24 47 PM](https://user-images.githubusercontent.com/120093816/216947540-8a4d62e2-52a3-4113-9b3f-943028cd002b.png)

카메라 위치 변경 후 실험
![Screen Shot 2023-02-06 at 7 27 22 PM](https://user-images.githubusercontent.com/120093816/216948147-249c120d-e4f8-4ce1-b656-66524a0b1a26.png)

<br><br>

### 실험 데이터

<img width="1964" alt="Screen Shot 2023-02-06 at 7 20 16 PM" src="https://user-images.githubusercontent.com/120093816/216946750-85592d42-6e4d-449f-96c1-a27fdc00eac3.png">










<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>
