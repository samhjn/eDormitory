from django.shortcuts import HttpResponse

# Create your views here.

def switchUpdate(request):
    id = request.GET.get('id',-1)
    status = request.GET.get('status',-1)
    if (status == -1) or (id == -1):
        return HttpResponse('{Status: 1}')
    return HttpResponse('{Status: 0}')


def login(request):
    request.session['logged_in']=1

    return HttpResponse('{Status: 0}')
