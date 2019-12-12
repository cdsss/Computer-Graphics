window.onload = function() {

    const file = document.getElementById("file-input");
    const canvas = document.getElementById("canvas");
    const audio = document.getElementById("audio");

    file.onchange = function() {

        // 获得音频文件
        const files = this.files;
        console.log('FILES[0]: ', files[0])
        audio.src = URL.createObjectURL(files[0]);

        // 初始化 canvas
        canvas.width = window.innerWidth;
        canvas.height = window.innerHeight;
        const ctx = canvas.getContext("2d");

        // 初始化音频上下文，初始化分析器
        const context = new AudioContext();
        const analyser = context.createAnalyser();
        analyser.fftSize = 8192; // 控制方块多少

        // 将音频节点，关联到 AudioContext 上
        let src = context.createMediaElementSource(audio);
        src.connect(analyser);
        analyser.connect(context.destination);

        // 获取 frequencyData
        const bufferLength = analyser.frequencyBinCount;
        const dataArray = new Uint8Array(bufferLength);

        const WIDTH = canvas.width;
        const HEIGHT = canvas.height;

        const barWidth = (WIDTH / bufferLength) * 13;

        let barHeight;
        let x = 0;

        function renderFrame() {
            requestAnimationFrame(renderFrame); // Takes callback function to invoke before rendering

            x = 0;

            // 更新频率数据
            analyser.getByteFrequencyData(dataArray);

            ctx.fillStyle = "rgba(0,0,0,0.2)"; // 背景填充色
            ctx.fillRect(0, 0, WIDTH, HEIGHT);

            let r, g, b;
            let bars = 118


            for (let i = 0; i < bars; i++) {
                barHeight = (dataArray[i] * 2.5);

                // 根据频率不同，绘制不同的颜色
                if (dataArray[i] > 210){
                    r = 108
                    g = 91
                    b = 123
                } else if (dataArray[i] > 200){
                    r = 192
                    g = 108
                    b = 132
                } else if (dataArray[i] > 180){
                    r = 246
                    g = 114
                    b = 128
                } else {
                    r = 248
                    g = 177
                    b = 149
                }


                ctx.fillStyle = `rgb(${r},${g},${b})`;
                ctx.fillRect(x, (HEIGHT - barHeight), barWidth, barHeight);


                x += barWidth + 10 // Gives 10px space between each bar
            }
        }
        // 播放音频
        audio.play();
        renderFrame();
    };
};