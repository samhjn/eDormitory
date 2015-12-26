from django.shortcuts import HttpResponse

# Create your views here.

def switchUpdate(request):
    return HttpResponse('{Status: 0}')


def login(request):
    request.session['logged_in']=1

    return HttpResponse('{Status: 0}')
