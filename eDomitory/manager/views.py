from django.shortcuts import render

# Create your views here.

def index(request):

    return render(request,'index.html',{'loggedIn': 1})

def login(request):

    return render(request,'index.html',{'loggedIn': 0})

def logout(request):

    return render(request,'index.html',{'loggedIn': 1})

def switch(request):

    return render(request,'switch.html',{'loggedIn': 1,'pageId': 1,'switches':[{'id':1,'name':'Door Lock','status':0},{'id':2,'name':'Lamp','status':3}]})


def sensor(request):

    return render(request,'sensor.html',{'loggedIn': 1,'pageId': 2})


def settings(request):

    return render(request,'index.html',{'loggedIn': 1})