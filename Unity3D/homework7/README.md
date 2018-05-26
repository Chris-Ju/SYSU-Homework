# 环形粒子

- 还是比较喜欢做这种很好看的作业
- (其实是因为比较简单)

- 不需要 prefab，只要使用 GameObject 便可

- 新建一个类来储存位置
    ```cs
    public class CirclePosition
    {
      public float radius = 0f;
      public float theta = 0f;
      public CirclePosition(float radius, float theta)
      {
        this.radius = radius;
        this.theta = theta;
      }

      public Vector3 generateCirclePosition(float z = 0)
      {
        return new Vector3(Mathf.Cos(this.theta) * this.radius, Mathf.Sin(this.theta) * this.radius, z);
      }
    }
    ```
- 通过 Gradient 来设置透明度渐变
    ```cs
    GradientAlphaKey[] alphakeys = new GradientAlphaKey[5];
    alphakeys[0].time = 0.0f;
    alphakeys[0].alpha = 1.0f;
    alphakeys[1].time = 0.4f;
    alphakeys[1].alpha = 0.4f;
    alphakeys[2].time = 0.6f;
    alphakeys[2].alpha = 1.0f;
    alphakeys[3].time = 0.9f;
    alphakeys[3].alpha = 0.4f;
    alphakeys[4].time = 1.0f;
    alphakeys[4].alpha = 0.9f;
    GradientColorKey[] colorkeys = new GradientColorKey[2];
    colorkeys[0].time = 0.0f;
    colorkeys[0].color = Color.white;
    colorkeys[1].time = 1.0f;
    colorkeys[1].color = Color.white;

    this.colorGradient = new Gradient();
    this.colorGradient.SetKeys(colorkeys, alphakeys);
    ```

- 使用了三角函数来完成定位
    ```cs
    for (int i = 0; i < this.count; i++)
    {
      float tmp_radius;
      float nAvg = 1 + this.notAvg;
      if (i < this.count / 2)
      {
        tmp_radius = Random.Range(this.midradius - this.haloSize / nAvg, this.midradius + this.haloSize / nAvg);
      }
      else
      {
        tmp_radius = Random.Range(this.midradius - this.haloSize, this.midradius + this.haloSize);
      }

      float theta = Random.Range(0f, 360f) * Mathf.PI / 180f;

      this.particlesArr[i].position = new Vector3(Mathf.Cos(theta) * tmp_radius, Mathf.Sin(theta) * tmp_radius, 0);
      this.positionArr[i] = new CirclePosition(tmp_radius, theta);
    }
    this.particleSys.SetParticles(particlesArr, particlesArr.Length);
    ```

- 愉快的作业体验~

[视频地址](https://youtu.be/ZBCulsDtD20)

<iframe width="560" height="315" src="https://www.youtube.com/embed/ZBCulsDtD20?rel=0" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>