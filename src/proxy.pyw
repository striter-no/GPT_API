from flask import Flask, request
import g4f

app = Flask(__name__)

@app.route('/', methods=["POST"])
def test():
	req = request.get_json()
	model = req["model"]
	prompt = req["req"]
	ans = g4f.ChatCompletion.create(
		model = ((g4f.models.gpt_4) if (model == "1") else (g4f.models.gpt_35_turbo)),
		messages = [{"role": "user", "content": prompt}]
	)
	
	return ans

app.run(host='0.0.0.0', port=900)