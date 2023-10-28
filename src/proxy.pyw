from flask import Flask, request
import g4f

g4f.debug.logging = True
app = Flask(__name__)

def getModel(mode):
	if mode == 0: return g4f.models.gpt_35_turbo
	else: return g4f.models.gpt_4

def getProvider(mode):
	if mode == 0: return g4f.Provider.AiAsk
	elif mode == 1: return g4f.Provider.MyShell
	elif mode == 2: return g4f.Provider.ChatBase
	else: return g4f.Provider.Phind

@app.route('/', methods=["POST"])
def test():
	req = request.get_data().decode("utf-8")
	model = int(req.split("#&x0S")[1])
	prov = int(req.split("#&x0S")[2])
	quest = "\n".join(req[5:].split("#&x0S")[3:])
	
	ans = g4f.ChatCompletion.create(
		model = getModel(model),
		messages = [{"role": "user", "content": quest}],
		provider = getProvider(prov)
	)
	print(g4f.annotations)
	return ans

app.run(host='0.0.0.0', port=900)