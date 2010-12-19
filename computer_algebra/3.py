R3.<x1, x2, x3, x4, x5, y1, y2, y3, y4, y5, y6, y7> = PolynomialRing(QQ, 12, order = 'lex')
I3 = ideal(y1 - x1^3 * x3^5,
           y2 - x1^2 * x3 * x2^4,
           y3 - x2^2 * x3^3,
           y4 - x2^3 * x1,
           y5 - x3 * x2 * x1 * x5,
           y6 - x4 * x5^2,
           y7 - x5 * x2^2 * x1^3)
B3 = I3.groebner_basis()
print "Groebner basis:"
for b in B3:
    print b

print "\nToric ideal basis:"
for b in B3:
    if set(b.variables()).intersection([x1, x2, x3, x4, x5]) == set():
        print b
