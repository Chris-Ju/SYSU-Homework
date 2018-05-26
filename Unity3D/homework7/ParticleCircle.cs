using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParticleCircle : MonoBehaviour
{

    [Header("粒子数量")]
    public int count = 10000;

    [Header("环的宽度")]
    public float haloSize = 0.5f;

    [Header("环的半径")]
    public float midradius = 5f;

    [Header("受控的粒子系统")]
    public ParticleSystem particleSys;

    [Header("渐变速度")]
    public float deltaAngle = 0.1f;
    private float delta_theta;

    [Header("不均匀分布度：0为完全均匀")]
    public float notAvg = 0f;

    [Header("粒子波动强度(PingPong)")]
    public float pingpong = 0.2f;

    private ParticleSystem.Particle[] particlesArr;
    private CirclePosition[] positionArr;
    private Gradient colorGradient;

    // Use this for initialization
    void Start()
    {
        this.particlesArr = new ParticleSystem.Particle[this.count];
        var particleMain = this.particleSys.main;
        particleMain.maxParticles = this.count;
        this.particleSys.Emit(this.count);
        this.particleSys.GetParticles(this.particlesArr);

        this.positionArr = new CirclePosition[this.count];
        this.delta_theta = this.deltaAngle * Mathf.PI / 180f;

        // 通过Gradient来设置透明度渐变
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
            // 这里需要转成弧度制
            float theta = Random.Range(0f, 360f) * Mathf.PI / 180f;
            // 用三角函数完成定位
            this.particlesArr[i].position = new Vector3(Mathf.Cos(theta) * tmp_radius, Mathf.Sin(theta) * tmp_radius, 0);
            this.positionArr[i] = new CirclePosition(tmp_radius, theta);
        }
        this.particleSys.SetParticles(particlesArr, particlesArr.Length);
    }

    // Update is called once per frame
    void Update()
    {
        for (int i = 0; i < this.count; i++)
        {
            positionArr[i].theta -= delta_theta;
            positionArr[i].radius += Mathf.PingPong(0.002f, pingpong) - Mathf.PingPong(0.002f, pingpong);
            particlesArr[i].position = positionArr[i].generateCirclePosition();
            particlesArr[i].startColor = colorGradient.Evaluate(positionArr[i].theta / (2 * Mathf.PI));
        }
        particleSys.SetParticles(particlesArr, particlesArr.Length);
    }
}

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