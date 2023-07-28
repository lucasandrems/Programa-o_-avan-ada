from django.http import HttpResponse
from django.shortcuts import render


def login(request):
    return render(request, 'login/login.html')


def home(request):
    return render(request, 'home/home.html')
