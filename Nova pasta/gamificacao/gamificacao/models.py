from django.contrib.auth.models import User
from django.db import models

# Create your models here.
CURSO = [
    ('quimica', 'Engenharia Química'),
    ('ambiental', 'Engenharia Ambiental'),
    ('alimentos', 'Engenharia Alimentos'),
]

class Membros(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE, blank=True)
    curso = models.CharField(max_length=50, choices=CURSO)
    matricula = models.IntegerField(default=0)

    def __str__(self):  
        return f'{self.user} - {self.matricula}'