from django.shortcuts import render,HttpResponseRedirect
from .models import SwitchInfo

# Create your views here.

def index(request):
    if request.session.get('logged_in',0) != 1:
        return HttpResponseRedirect('/login/')

    return render(request,'index.html',{'loggedIn': 1})


def login(request):
    if request.session.get('logged_in',0) == 1:
        return HttpResponseRedirect('/')

    return render(request,'index.html',{'loggedIn': 0})


def logout(request):
    try:
        del request.session['logged_in']
    except KeyError:
        pass

    return HttpResponseRedirect('/login/')


def switch(request):
    switches=[]

    if request.session.get('logged_in',0) != 1:
        return HttpResponseRedirect('/login/')

    switchData = SwitchInfo.objects.all()
    for i in switchData:
        switches.append({'id': i.id, 'name': i.name, 'status': i.status})

    return render(request,'switch.html',{'loggedIn': 1,'pageId': 1,'switches': switches})


def sensor(request):
    if request.session.get('logged_in',0) != 1:
        return HttpResponseRedirect('/login/')

    return render(request,'sensor.html',{'loggedIn': 1,'pageId': 2})


def settings(request):
    if request.session.get('logged_in',0) != 1:
        return HttpResponseRedirect('/login/')

    return render(request,'index.html',{'loggedIn': 1})
