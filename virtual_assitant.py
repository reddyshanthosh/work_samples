import wolframalpha
import wikipedia
import PySimpleGUI as sg
import pyttsx3
import speech_recognition as sr

"""
Description:

Virtual Assitant that solves mathematical equations and shows wikipedia results based on Text input in the chatbot or using speech recognition.
Implementation of Text to speech and speech to text functionality has been added. This app is still in development phase. 


Tools:
Python, Wolfram Api, Wikipedia Api, speechrecognition, pyaudio, sphinx, pocketsphinx

"""

client = wolframalpha.Client("2YYVPY-PJY3PRWV2P")
sg.theme('DarkAmber')	# Add a touch of color
# All the stuff inside your window.
layout = [[sg.Text('Enter a command'), sg.InputText()],
            [sg.Button('Ok'), sg.Button('Cancel')]]
window = sg.Window('Virtual Assitant', layout)

engine = pyttsx3.init()


while True:
	# obtain audio from the microphone
	r = sr.Recognizer()
	with sr.Microphone() as source:
	    print("Say something!")
	    audio = r.listen(source)

	# recognize speech using Sphinx
	try:
	    print("Sphinx thinks you said " + r.recognize_sphinx(audio))
	except sr.UnknownValueError:
	    print("Sphinx could not understand audio")
	except sr.RequestError as e:
	    print("Sphinx error; {0}".format(e))

	event, values = window.read()
	if event in (None,'Cancel'):
		break
	try:
		wiki_res = wikipedia.summary(values[0], sentences=2)
		wolfram_result = next(client.query(values[0]).results).text	
		engine.say("Wolfram Result is:" + wolfram_result)
		sg.PopupNonBlocking("Wolfram Result:" + wolfram_result, "Wikipedia Result:"+wiki_res)
	except wikipedia.exceptions.DisambiguationError:
		wolfram_result = next(client.query(values[0]).results).text	
		engine.say("Wolfram Result is:" + wolfram_result)
		sg.PopupNonBlocking("Wolfram Result:" + wolfram_result)
	except wikipedia.exceptions.PageError:
		wolfram_result = next(client.query(values[0]).results).text	
		engine.say("Wolfram Result is:" + wolfram_result)
		sg.PopupNonBlocking("Wolfram Result:" + wolfram_result)
	except:
		wiki_res = wikipedia.summary(values[0], sentences=2)
		engine.say("According to Wikipedia:" + wiki_res)
		sg.PopupNonBlocking("According to Wikipedia:" + wiki_res)
	engine.runAndWait()

		
window.close()