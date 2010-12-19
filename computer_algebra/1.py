R.<x1,x2,y1,y2,y3> = PolynomialRing(QQ, 5, order = 'lex')
I = ideal(y1 - x1^2 * x2,
          y2 - x1^7 * x2^5,
          y3 - x1^4 * x2^3)

B = I.groebner_basis()
print "Groebner basis:"
for b in B:
    print b

print "\nToric ideal basis:"
for b in B:
    if set(b.variables()).intersection([x1, x2]) == set():
        print b
