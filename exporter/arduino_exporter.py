import serial
from flask import Flask, Response

PORT = "/dev/arduino"
BAUD = 115200

ser = serial.Serial(PORT, BAUD, timeout=2)

app = Flask(__name__)

metrics = {}

def parse_line(line: str):
    # Expected format: metric_name value
    parts = line.split()
    if len(parts) == 2:
        name, value = parts
        try:
            metrics[name] = float(value)
        except ValueError:
            pass

def read_serial():
    while True:
        line = ser.readline().decode(errors="ignore").strip()
        if line:
            parse_line(line)

@app.route("/metrics")
def metrics_endpoint():
    output = []
    for name, value in metrics.items():
        output.append(f"{name} {value}")
    return Response("\n".join(output) + "\n",
                    mimetype="text/plain")

if __name__ == "__main__":
    import threading
    t = threading.Thread(target=read_serial, daemon=True)
    t.start()
    app.run(host="0.0.0.0", port=9100)

