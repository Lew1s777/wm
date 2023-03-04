static void selectlayout(const Arg *arg);
static void incnmaster(const Arg *arg);
static void toggleborder(const Arg *arg);

void
selectlayout(const Arg *arg)
{
    const Layout *cur = selmon->lt[selmon->sellt];
    const Layout *target = cur == arg->v ? &layouts[0] : arg->v;
    setlayout(&(Arg) { .v = target });
}

void
incnmaster(const Arg *arg)
{
    int nmaster = selmon->nmaster + arg->i;
    if (selmon->bt <= 1)
        nmaster = 1;
    else if (nmaster >= 3)
        nmaster = 1;
    selmon->nmaster = selmon->pertag->nmasters[selmon->pertag->curtag] = MAX(nmaster, 1);
    arrange(selmon);
}

void
toggleborder(const Arg *arg)
{//Strange flicker with picom
    if (!selmon->sel)
        return;
    selmon->sel->isnoborder ^= 1;
    selmon->sel->bw = selmon->sel->isnoborder ? 0 : borderpx;
    int diff = (selmon->sel->isnoborder ? -1 : 1) * borderpx;
    resizeclient(
        selmon->sel,
        selmon->sel->x - diff,
        selmon->sel->y - diff,
        selmon->sel->w,
        selmon->sel->h
    );
    focus(NULL);
}
