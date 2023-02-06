
## Homography
![](https://velog.velcdn.com/images/ian-k-developer/post/3ab7f3d3-9705-408d-a258-0efcb3959be4/image.png)


두 평면사이의 Perspective Transform(원근 변환, 투시 변환) 관계이다.
카메라로부터 실제로 얼마나 멀리 떨어져 있고 또 키는 얼마나 큰지 알아내는 것은 영상기하학의 가장 빈번한 응용 중 하나

영상내 임의의 영상좌표(픽셀좌표)에 대해 대응되는 2D 지면좌표(ground plane coordinate)를 구하는 문제로 귀결

![](https://velog.velcdn.com/images/ian-k-developer/post/6c414ad9-392c-41c1-9978-93d08a843143/image.png)


임의의 네 대응쌍을 이용해서 구한 H를 다른 모든 점들에 대해서도 동일하게 적용할 수 있다



### Homography matrix
![](https://velog.velcdn.com/images/ian-k-developer/post/631e71f7-402c-404d-85b9-238d40bb6161/image.png)


`h33` 은 1로 일정하며, `w` 는 scale factor로, `h31`과 `h32`의 합으로 표현되는 변수이므로 8개의 h를 알아내야 하므 로 4쌍의 대응점이 필요하다. 이를 연립방정식을 통하여 얻어낼 수 있다.
=> 기준점을 4개로 잡은 이유

`h31`과 `h32`는 변환된 후의 평면의 기울어진 방향과 기울어진 정도를 알아낼 수 있는 벡터이다.
`h13`과 `h23`은 평행 이동한 벡터를 나타낸다.
`h11`, `h12`, `h21`, `h22`는 평행이동, 팽창 수축, 회전, 평면의 기울어짐 등이 종합적으로 반영되어
있다.

식을 풀면,

![](https://velog.velcdn.com/images/ian-k-developer/post/d6aa0a60-3397-4b27-9433-00b7cdf07e32/image.png)


x, y에 대한 식으로 표현하면,

![](https://velog.velcdn.com/images/ian-k-developer/post/f31e8ab8-e74f-4763-8d8c-62b670bd5199/image.png)


이를 행렬로 표현하면,

![](https://velog.velcdn.com/images/ian-k-developer/post/91d3fbf8-efd0-4f9f-9df6-149d45983424/image.png)






이며, 역행렬을 통해 H를 구한다. 

![](https://velog.velcdn.com/images/ian-k-developer/post/00ed65bf-c673-485d-ae2e-0a62b24108a8/image.png)



## 소실선

물리공간에서 평행한 모든 직선들은 영상에서 모두 동일한 소실점을 갖는다.

![](https://velog.velcdn.com/images/ian-k-developer/post/478a540b-af56-4d2a-8c0d-97956a7c54c4/image.jpeg)

![](https://velog.velcdn.com/images/ian-k-developer/post/83e401e7-b5a6-4564-a634-2adb9455f3d5/image.png)


동일 평면에 속한 직선들의 소실점들은 모두 일직선상에 존재하게 되는데 이 선을 소실선이라고 한다

![](https://velog.velcdn.com/images/ian-k-developer/post/6828b1f6-b788-4140-a8bf-bc7639da70f6/image.png)


기하학적으로 봤을 때, 어떤 평면에 대한 소실선(vanishing line)은 이 평면과 수평이고 카메라 원점을 지나는 평면이 이미지 평면과 만나서 생기는 교선이다.
소실점(vanishing point)도 마찬가지이다. 지면 위의 한 직선을 이미지에 투영해 보면 직선을 무한히 확장하였을 경우 결국 소실선(L) 상의 어느 한 점으로 수렴하게 됨을 쉽게 상상할 수 있다.

![](https://velog.velcdn.com/images/ian-k-developer/post/a9314811-75a3-42bb-aace-7ca0f2e85652/image.png)


소실선을 이용하여 현재 자세를 구할 수 있다. 수평선과 비슷한(지구는 둥글기 때문에 완전 같지는 않다.) 특징을 가지고 있어서 내가 바닥과 수평 방향을 바라보고 있다면 **내 시야에 중심에 소실선이 정확하게 일치**하게 되며 소실선이 내 시야중심보다 아래 있으면 내가 위를 바라보고 있는 것이고 반대로 위에 있으면 내가 아래를 바라보는 것이므로 **내가 어느 각도로 바라보고 있는지 소실선을 통해 알 수 있다**. 


![](https://velog.velcdn.com/images/ian-k-developer/post/7bd0664a-6b0c-4e76-a468-2b359c51931c/image.png)


소실선의 위치를 알면 캘리브레이션을 하지 않고도 카메라의 팬(pan), 틸트(tilt), 롤(roll)을 알아낼 수 있다.



## Posture

소실선과 롤(roll)

![](https://velog.velcdn.com/images/ian-k-developer/post/c734b207-7e76-48dc-89a3-9c7ff83f0c69/image.jpeg)
![](https://velog.velcdn.com/images/ian-k-developer/post/5be59f89-6540-400e-b722-11b55be31074/image.png)


소실선과 틸트(tilt)

![](https://velog.velcdn.com/images/ian-k-developer/post/e4296165-4bfe-43c0-8583-99c43b7021f2/image.png)

소실점의 y 좌표를 알면 카메라의 틸트(tilt)는 다음과 같이 간단하게 계산된다.
vy는 소실점의 y좌표(픽셀좌표), 
cy는 주점의 y좌표, 
fy는 y축 방향 카메라 초점거리.



![](https://velog.velcdn.com/images/ian-k-developer/post/cdd3a335-f0af-45d3-9eae-5dfac1c41514/image.png)

roll 회전이 존재하는 경우에는 소실점만으로는 문제 해결이 안되며 소실선(vanishing line) 정보가 필요하다. 소실선이 주어질 경우, 카메라 주점과 소실선의 수직거리를 d(픽셀 단위), 초점거리를 f라 하면 틸트는 θtilt = atan2(d, f)로 계산

소실선과 팬(pan)
![](https://velog.velcdn.com/images/ian-k-developer/post/fd26f19c-0678-458c-ba50-0a2b802aeda1/image.png)

카메라의 원점을 C, 이미지의 주점을 P, 소실점을 V, 초점거리를 f, 주점에서 소실선에 내린 수선의 발을 H, 수직거리를 d
![](https://velog.velcdn.com/images/ian-k-developer/post/d245f7c0-dec6-47a7-96fe-34281c965271/image.png)

사진에서 자세를 기술하는 용어중에 카메라의 팬(pan), 틸트(tilt), 롤(roll) 개념이 있다. Tilt는 위, 아래를 바라보는 것이고, Roll은 갸우뚱하게 바라보는 것이고, Pan은 좌, 우로 바라보는 것이다.  이 개념으로 사용자의 자세를 기술 할 수 있다.
위치는 시야중심과 QR코드의 중심이 일치할 때에 있다. 이 경우에는 내 자세가 바로 나의 위치를 결정지을 수 있게 되는데 그 이유는 코드에서 카메라로 이은 가상의 선과 카매라의 시야 중심을 따라 이은 선이 일치하기 때문이다. 여기서 힌트를 얻어서 현재의 자세 정보에다가 코드 중심과 시야중심과의 차이 벡터를 통하여 사용자의 위치를 얻을 수 있다고 생각하게 되었으며 이것을 기반으로 프로그램을 구현하고 있다.

* Roll : 사용자의 시야에 의해 생기는 평행선과 소실선과의 각도
* Tilt : 사용자의 theta방향 자세
* Pan : 사용자의 phi방향 자세

![](https://velog.velcdn.com/images/ian-k-developer/post/8821cc0f-7e67-4836-bcaf-b8d6697204a5/image.png)

![](https://velog.velcdn.com/images/ian-k-developer/post/f3a18599-cc69-4165-9cda-99581688380e/image.png)

![](https://velog.velcdn.com/images/ian-k-developer/post/4408e602-bf6c-4ac2-afe3-ccc70b694fe0/image.png)



두 개 이상의 소실점을 통해 소실선을 구할 수 있다. 위에서 언급했듯이 소실선은 서로 다른 두 개 이상의 소실점을 통해 구할 수 있는데 오차를 줄이기 위해 여러 개의 소실점을 통해 구하기로 한다. 호모그래피 행렬의 내부의 값을 통해서 다수의 소실점을 구할 수 있다.

소실 점이란 무한히 긴 직선이 기울어져 있어서 나타나는 수렴하는 점이다. 이와 같은 특성을 이용 해서 x, y 값을 어떤 직선을 따라 무한히 증가(혹은 감소) 시킬 때 x’, y’ 값이 수렴한다면 이것이 소실점이 될 것이며, 직선을 평행하지 않은 다른 직선으로 바꾸어서 x,y 값을 증가시키면 다른 소실점이 나올 수 있다.



## Location
RGBY 평면의 크기를 통해 코드와의 거리 계산

어떤 한 선분을 보는 각도는 유지한 체로 거리만 멀어지면서 관찰하면 그 길이가 거리와 반비례 관계로 나타난다. 하지만 이것을 이용하기 위해선 각도가 변하지 않는다는 조건이 필요하다. 이것을 보완하기 위해 기준이 되는 코드 좌표공간에서 정해진 반지름으로 원을 그린 뒤 구해진 호모그래피를 이용하여 해당하는 점들을 변환된 코드 좌표공간으로 이동시킨다. 이렇게 하면 원이 찌그러져서 타원이 될 텐데 이 타원에서 가장 긴 지름이 바로 위에서 말한 각도가 유지된 체 거리만 바뀐 선분이다

![](https://velog.velcdn.com/images/ian-k-developer/post/92c4c9aa-98c7-4f76-ae25-f3b3caa55e68/image.png)

왜냐하면 위의 두 그림과 같이 기울어진 방향으로는 원이 압축되지만 기울어지지 않은 방향으로는 그 길이가 유지 되기 때문이다. 타원의 긴 지름은 기울어짐으로 인한 선분의 길이 감소가 일어나지 않으므로 이것을 기준으로 코드와 나와의 거리를 측정하는데 사용하기에 적합하다.
 
다만 이 방법은 원 위의 점의 갯수만큼 호모그래피 변환을 실시해야 하며 지름을 찾기 위해 가장 거리가 먼 두 점을 찾는 등 연산량이 많아서 프로그램을 느리게 할 가능성이 있다. 그래서 타원의 가장 긴 지름이 소실선으로 향하는 가장 짧은 벡터와 항상 수직하다는 점을 이용하여 타원의 긴 지름을 쉽게 구하도록 하였다.



### 설계
1) RGBY 평면
RGB와 Yellow 색의 4개의 기준점을 가진 평면

![](https://velog.velcdn.com/images/ian-k-developer/post/69ed8c5d-1ab9-466c-ba1c-d2c672f5173a/image.png)

2) 기준 평면의 소실선 벡터

그림판을 통해 픽셀 좌표를 알 수 있다. 호모그래피 프로그램에 기준이되는 QR코드의 RGB Yellow점의 좌표를 넣어 QR코드의 중앙점을 (0,0)으로 맞춘 후 (임의의 점이지만 편하게 하기 위하여) 호모그래피 행렬을 통해 
```
	1.(x=∞, y=0) 
	2.(x=0, y=∞) 
	3.(x=∞, y=∞)
```

으로 보내는 세 개의 소실점을 통해 무조건 나오는 2개의 소실점을 찾은 후 소실선 벡터를 구한다. 
![](https://velog.velcdn.com/images/ian-k-developer/post/cf2b283d-b421-49f7-85ca-77a4f92c450e/image.png)

3) 두번째 평면의 소실선 벡터

두번째 평면은 사용자가 기준 평면을 사진으로 찍은 왜곡이 있는 평면이다. RGB Yellow 점의 좌표를 넣어주고 마찬가지로 호모그래피 행렬을 통해 소실선 벡터를 구해준다.
![](https://velog.velcdn.com/images/ian-k-developer/post/8a0cf046-ed78-4581-b765-b4f70366d23f/image.png)

![](https://velog.velcdn.com/images/ian-k-developer/post/b53255f8-0a7f-46fd-9284-01b01a1e5a89/image.png)

->호모그래피 행렬 계산을 통한 소실선벡터 도출

4) 미리 실험을 통해 얻어놓은 `각도에 따른 픽셀좌표`와 `픽셀수 샘플`과 비교를 하여 두개의 소실선의 각도 차이를 얻어낸다.

![](https://velog.velcdn.com/images/ian-k-developer/post/0ab31441-1351-45c6-9e6a-f75669f1d52f/image.png)




5) QR격자 크기를 통해 코드와의 거리를 계산한다.

![](https://velog.velcdn.com/images/ian-k-developer/post/5ce5c967-84aa-4805-bb5c-162501a091ba/image.png)


호모그래피를 이용하여 해당하는 점들을 변환된 코드 좌표공간으로 이동시킨다. 이렇게 하면 원이 찌그러져서 타원이 될 텐데 이 타원에서 가장 긴 지름이 바로 위에서 말한 각도가 유지된 체 거리만 바뀐 선분이다.타원의 긴 지름은 기울어짐으로 인한 선분의 길이 감소가 일어나지 않으므로 이것을 기준으로 코드와 나와의 거리를 측정하는데 사용






### Trouble Shooting
설계 시 문제점, 그리고 해결 방안

문제점 1)
호모그래피를 구할때 opencv의 함수로 구하려고 했으나 호모그래피 내부 변수를 빼낼 수가 없었다.

해결방안: 직접 호모그래피를 구하는 함수를 만들어서 그 변수값을 구함

문제점 2)
소실선을 구하여 소실선과 화면 중심간에 픽셀 거리를 알았다고 하더라도 픽셀간격과 실제 각도와의 관계를 모른다.

해결방안: 실험을 통해 Data를 얻는다.
```
1. Θ값 샘플 데이터 
2. π값 샘플 데이터
3. 각도와 픽셀의 상관관계 

```



실험 1.

- 평면을 5도 간격으로 측정하여 샘플을 얻는다.
- 호모그래피 프로그램에 평면의 RGB ,Yellow 점의 좌표 삽입 
- 소실선 벡터 얻은 후 시야중심과 소실선의 각 Θ 도출

![](https://velog.velcdn.com/images/ian-k-developer/post/e6d0a72d-fd3f-48ca-ad35-bed4733ba638/image.png)



-------------------------------------------------

실험 2.

- 평면의 회전을 10도마다 측정하여 샘플을 얻는다.
- 호모그래피 프로그램에 평면의 RGB ,Yellow 점의 좌표 삽입 
- 소실선 벡터 얻은 후 시야중심과 소실선의 각 π 도출

![](https://velog.velcdn.com/images/ian-k-developer/post/6a9f3f10-274e-41aa-8274-5b956fb53588/image.png)



-------------------------------------------------



실험 3. 

각도에 따른 픽셀 샘플수를 얻기위해 사진을 찍어 픽셀을 계산한다.
![](https://velog.velcdn.com/images/ian-k-developer/post/2c19c628-1d95-4a1f-8766-bcc78c71586e/image.png)




픽셀 값을 측정하기 위해 렌즈의 시야각에 맞게 선을 그은 후 10도 단위로 선을 그었다. 일자로 보이게 셋팅한 후 촬영하였다.


![](https://velog.velcdn.com/images/ian-k-developer/post/692cb298-24c1-4d86-a812-6268cec08af0/image.JPG)
